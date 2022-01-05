#pragma once
#include <memory>
#include <map>
#include <fstream>

#include "../addons/ILogger.h"
#include "../sys/exception/LekserReaderException.h"

namespace Lex
{
	class LekserDefinitionReader
	{
		std::shared_ptr<ILogger> log;
		std::map<std::string, std::string> definitions;

		std::string readToken(std::string::iterator& it, std::string::iterator end);
		std::string readRegex(std::string::iterator it, std::string::iterator end);
		std::string removeVariables(std::string definition);
	public:
		LekserDefinitionReader(std::shared_ptr<ILogger> log);
		std::map < std::string, std::string> readDefinition(std::string fileName);
		std::string getRegexForVariable(std::string variable);
	};
}
