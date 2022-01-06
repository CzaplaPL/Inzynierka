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
		std::map<std::string, std::string> definitions;
		std::vector<Definition> generateVector(std::map<std::string, std::string> definitions);
		std::string readToken(std::string::iterator& it, std::string::iterator end);
		std::string readRegex(std::string::iterator it, std::string::iterator end);
		std::string removeVariables(std::string definition);
	public:
		LekserDefinitionReader(std::shared_ptr<ILogger> log);
		std::vector<Definition> readDefinition(std::string fileName);
		std::string getRegexForVariable(std::string variable);
	};
}
