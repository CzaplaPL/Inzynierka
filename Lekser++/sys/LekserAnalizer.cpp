#include "LekserAnalizer.h"

std::vector<Token> Lex::LekserAnalizer::analizeFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::vector<Token> toReturn;
	if (!file.is_open())
	{
		this->log->error("nie uda³o otworzyc pliku z definicjami : " + fileName);
		return toReturn;
	}
	std::string line;
	int numberLine = 1;
	while (std::getline(file, line))
	{
		try
		{
			std::vector<Token> analizeResult = this->analizeLine(line);
			toReturn.insert(toReturn.end(), analizeResult.begin(), analizeResult.end());
		}
		catch (NoStepException noStep)
		{
			this->log->error("b³¹d analizy w lini(" + std::to_string(numberLine) + ") : " + noStep.what());
			return toReturn;
		}
		numberLine++;
	}
	return toReturn;
}

std::vector<Token> Lex::LekserAnalizer::analize(std::string text)
{
	std::vector<Token> toReturn;
	std::string line;
	int numberLine = 1;
	std::istringstream textStream(text);
	while (std::getline(textStream, line))
	{
		try
		{
			std::vector<Token> analizeResult = this->analizeLine(line);
			toReturn.insert(toReturn.end(), analizeResult.begin(), analizeResult.end());
		}
		catch (NoStepException noStep)
		{
			this->log->error("b³¹d analizy w lini(" + std::to_string(numberLine) + ") : " + noStep.what());
			return toReturn;
		}
		numberLine++;
	}
	return toReturn;
}

std::vector<Token> Lex::LekserAnalizer::analizeLine(std::string line)
{
	std::vector<Token> toReturn;
	MachineStep actualStep = this->das->getFirstStep();
	std::string value = "";
	for (std::string::iterator it = line.begin(); it != line.end(); ++it)
	{
		try
		{
			std::string nextStepId = actualStep.getStepIdForString(std::string(1, *it));
			value += *it;
			actualStep = this->das->getStep(nextStepId);
		}
		catch (NoStepException noStep)
		{
			if (actualStep.stepIsAccepting())
			{
				toReturn.push_back(Token(actualStep.getAcceptingToken(), value));
				this->das->runCallbackForToken(actualStep.getAcceptingToken(), value);
				actualStep = this->das->getFirstStep();
				value = "";
				it--;
			}
			else if (actualStep.getId() == this->das->getFirstStepId() && std::isspace(*it))
			{
				value = "";
				continue;
			}
			else
			{
				throw NoStepException(noStep.what());
			}
		}
	}
	if (actualStep.stepIsAccepting())
	{
		toReturn.push_back(Token(actualStep.getAcceptingToken(), value));
		this->das->runCallbackForToken(actualStep.getAcceptingToken(), value);
		return toReturn;
	}
	else if (actualStep.getId() != this->das->getFirstStepId())
	{
		throw NoStepException("ostatnie znaki nie tworza tokenu");
	}
	return toReturn;
}