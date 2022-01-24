#pragma once

#include <memory>
#include <map>
#include <vector>
#include <fstream>

#include "../addons/ILogger.h"
#include "../sys/exception/LekserReaderException.h"
#include "Rule.h"

namespace Lex
{
	class LekserRuleReader
	{
		std::shared_ptr<ILogger> log;
		std::vector<Rule> rules;
		Rule findDefinition(std::string token);
		std::string readToken(std::string::iterator& it, std::string::iterator end);
		std::string readRegex(std::string::iterator it, std::string::iterator end);
		std::string removeVariables(std::string definition);
		std::string getRegexForVariable(std::string variable);
	public:
		LekserRuleReader(std::shared_ptr<ILogger> log);
		std::vector<Rule> readRule(std::string fileName);
		std::vector<Lex::Rule> addRule(std::string token, std::string regex);
		std::vector<Rule> ruleFromMap(std::vector<std::pair<std::string, std::string>> tokenMap);
	};
}
