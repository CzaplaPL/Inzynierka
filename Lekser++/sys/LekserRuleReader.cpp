#include "LekserRuleReader.h"

Lex::LekserRuleReader::LekserRuleReader(std::shared_ptr <ILogger> log)
{
	this->log = log;
}

std::vector<Lex::Rule> Lex::LekserRuleReader::readRule(std::string fileName)
{
	this->rules.clear();
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		this->log->error("nie uda³o otworzyc pliku z definicjami : " + fileName);
		return std::vector<Lex::Rule>();
	}

	std::string line;
	int numberLine = 1;
	while (std::getline(file, line))
	{
		try
		{
			std::string::iterator it = line.begin();
			std::string token = this->readToken(it, line.end());
			it++;
			std::string regex = this->readRegex(it, line.end());
			regex = this->removeVariables(regex);
			this->rules.push_back(Rule(regex, token));
		}
		catch (LekserReaderException exception)
		{
			this->log->error(exception.what() + std::to_string(numberLine));
			return std::vector<Lex::Rule>();
		}
		numberLine++;
	}

	return this->rules;
}

std::vector<Lex::Rule> Lex::LekserRuleReader::addRule(std::string token, std::string regex)
{
	try
	{
		regex = this->removeVariables(regex);
		this->rules.push_back(Rule(regex, token));
	}
	catch (LekserReaderException exception)
	{
		this->log->error(exception.what());
		return this->rules;
	}
	return this->rules;
}

std::vector<Lex::Rule> Lex::LekserRuleReader::ruleFromMap(std::vector<std::pair<std::string, std::string>> tokenMap)
{
	this->rules.clear();
	for (auto element : tokenMap)
	{
		try
		{
			std::string regex = this->removeVariables(element.second);
			this->rules.push_back(Rule(regex, element.first));
		}
		catch (LekserReaderException exception)
		{
			this->log->error(exception.what() + element.first);
			return std::vector<Lex::Rule>();
		}
	}
	return this->rules;
}

std::string Lex::LekserRuleReader::getRegexForVariable(std::string variable)
{
	return this->findDefinition(variable).getRegex();
}

Lex::Rule Lex::LekserRuleReader::findDefinition(std::string token)
{
	auto it = std::find_if(this->rules.begin(), this->rules.end(), [token](Rule def) -> bool {return def.getToken() == token; });
	if (it == this->rules.end()) throw LekserReaderException("nie odnaleziono zmiennej w lini : ");
	return *it;
}

std::string Lex::LekserRuleReader::readToken(std::string::iterator& it, std::string::iterator end)
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

std::string Lex::LekserRuleReader::readRegex(std::string::iterator it, std::string::iterator end)
{
	std::string regex = "";
	for (; it != end; ++it)
	{
		regex += *it;
	}
	return regex;
}

std::string Lex::LekserRuleReader::removeVariables(std::string definition)
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
			std::string regex = "(" + this->getRegexForVariable(variable) + ")";
			definition.replace(startIndex, endIndex + 1 - startIndex, regex);
			i = startIndex + regex.length() - 1;
			startIndex = -1;
		}
	}
	if (startIndex != -1) throw LekserReaderException("zabrak³o znaku $ w zmiennej w lini : ");
	return definition;
}