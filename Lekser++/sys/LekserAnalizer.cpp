#include "LekserAnalizer.h"

std::vector<std::string> Lex::LekserAnalizer::analizeFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::vector<std::string> toReturn;
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
			std::vector<std::string> analizeResult = this->analizeLine(line);
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

std::vector<std::string> Lex::LekserAnalizer::analize(std::string text)
{
	std::vector<std::string> toReturn;
	std::string line;
	int numberLine = 1;
	std::istringstream textStream(text);
	while (std::getline(textStream, line))
	{
		try
		{
			std::vector<std::string> analizeResult = this->analizeLine(line);
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

std::vector<std::string> Lex::LekserAnalizer::analizeLine(std::string line)
{
	std::vector<std::string> toReturn;
	MachineStep actualStep = this->das->getFirstStep();
	for (std::string::iterator it = line.begin(); it != line.end(); ++it)
	{
		try
		{
			std::string nextStepId = actualStep.getStepIdForString(std::string(1, *it));
			actualStep = this->das->getStep(nextStepId);
		}
		catch (NoStepException noStep)
		{
			if (actualStep.stepIsAccepting())
			{
				toReturn.push_back(actualStep.getAcceptingToken());
				actualStep = this->das->getFirstStep();
				it--;
			}
			else if (actualStep.getId() == this->das->getFirstStepId() && std::isspace(*it))
			{
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
		toReturn.push_back(actualStep.getAcceptingToken());
		actualStep = this->das->getFirstStep();
		return toReturn;
	}
	else if (actualStep.getId() != this->das->getFirstStepId())
	{
		throw NoStepException("ostatnie znaki nie tworza tokenu");
	}
	return toReturn;
}