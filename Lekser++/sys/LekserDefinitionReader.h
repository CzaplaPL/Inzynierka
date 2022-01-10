#pragma once

#include <memory>
#include <map>
#include <vector>
#include <fstream>

#include "../addons/ILogger.h"
#include "../sys/exception/LekserReaderException.h"
#include "Definition.h"

namespace Lex
{
	class LekserDefinitionReader
	{
		std::shared_ptr<ILogger> log;
		std::vector<Definition> definitions;
		Definition findDefinition(std::string token);
		std::string readToken(std::string::iterator& it, std::string::iterator end);
		std::string readRegex(std::string::iterator it, std::string::iterator end);
		std::string removeVariables(std::string definition);
	public:
		LekserDefinitionReader(std::shared_ptr<ILogger> log);
		std::vector<Definition> readDefinition(std::string fileName);
		std::vector<Lex::Definition> addDefinition(std::string token, std::string regex);
		std::vector<Definition> definitionfromMap(std::vector<std::pair<std::string, std::string>> tokenMap);
		std::string getRegexForVariable(std::string variable);
	};
}
