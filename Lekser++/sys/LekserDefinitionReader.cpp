#include "LekserDefinitionReader.h"

Lex::LekserDefinitionReader::LekserDefinitionReader(std::shared_ptr <ILogger> log)
{
	this->log = log;
}

std::vector<Lex::Definition> Lex::LekserDefinitionReader::readDefinition(std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		this->log->error("nie uda³o otworzyc pliku z definicjami : " + fileName);
		return std::vector<Lex::Definition>();
	}

	std::string line;
	int numberLine = 0;
	while (std::getline(file, line))
	{
		try
		{
			std::string::iterator it = line.begin();
			std::string token = this->readToken(it, line.end());
			it++;
			std::string regex = this->readRegex(it, line.end());
			regex = this->removeVariables(regex);
			this->definitions.insert(std::pair<std::string, std::string>(token, regex));
		}
		catch (LekserReaderException exception)
		{
			this->log->error(exception.what() + std::to_string(numberLine));
		}
		numberLine++;
	}

	return this->generateVector(this->definitions);
}

std::vector<Lex::Definition> Lex::LekserDefinitionReader::addDefinition(std::string token, std::string regex)
{
	regex = this->removeVariables(regex);
	this->definitions.insert(std::pair<std::string, std::string>(token, regex));
	return this->generateVector(this->definitions);
}

std::vector<Lex::Definition> Lex::LekserDefinitionReader::definitionfromMap(std::vector<std::pair<std::string, std::string>> tokenMap)
{
	for (auto element : tokenMap)
	{
		try
		{
			std::string regex = this->removeVariables(element.second);
			this->definitions.insert(std::pair<std::string, std::string>(element.first, regex));
		}
		catch (LekserReaderException exception)
		{
			this->log->error(exception.what());
		}
	}
	return this->generateVector(this->definitions);
}

std::string Lex::LekserDefinitionReader::getRegexForVariable(std::string variable)
{
	if (this->definitions.find(variable) == this->definitions.end()) throw LekserReaderException("nie odnaleziono zmiennej w lini : ");
	return this->definitions[variable];
}

std::vector<Lex::Definition> Lex::LekserDefinitionReader::generateVector(std::map<std::string, std::string> definitions)
{
	std::vector<Lex::Definition> toReturn;
	for (auto element : definitions)
	{
		toReturn.push_back(Definition(element.second, element.first));
	}
	return toReturn;
}

std::string Lex::LekserDefinitionReader::readToken(std::string::iterator& it, std::string::iterator end)
{
	std::string token = "";
	for (; it != end; ++it)
	{
		if (*it == ':')
		{
			return token;
		}
		token += *it;
	}
	throw LekserReaderException("b³¹d w odczytaniu definicji w lini : ");
}

std::string Lex::LekserDefinitionReader::readRegex(std::string::iterator it, std::string::iterator end)
{
	std::string regex = "";
	for (; it != end; ++it)
	{
		regex += *it;
	}
	return regex;
}

std::string Lex::LekserDefinitionReader::removeVariables(std::string definition)
{
	int startIndex = -1;
	int endIndex = -1;
	for (size_t i = 0; i < definition.size(); ++i)
	{
		if (definition[i] == '\\')
		{
			i++;
			continue;
		}
		if (definition[i] == '$' && startIndex == -1)
		{
			startIndex = i;
			continue;
		}
		if (definition[i] == '$' && startIndex != -1)
		{
			endIndex = i;
			std::string variable = definition.substr(startIndex + 1, endIndex - startIndex - 1);
			std::string regex = this->getRegexForVariable(variable);
			definition.replace(startIndex, endIndex + 1, regex);
			i = startIndex + regex.length() - 1;
			startIndex = -1;
		}
	}
	if (startIndex != -1) throw LekserReaderException("zabrak³o znaku $ w zmiennej w lini : ");
	return definition;
}