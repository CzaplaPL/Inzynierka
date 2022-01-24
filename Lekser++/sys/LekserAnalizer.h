#pragma once

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../addons/ILogger.h"
#include "../sys/Token.h"
#include "../Das/Das.h"
#include "exception/NoStepException.h"

namespace Lex
{
	class LekserAnalizer
	{
		std::shared_ptr<ILogger> log;
		Das* das;
		std::vector<Token> analizeLine(std::string line);
	public:
		LekserAnalizer(std::shared_ptr<ILogger> logger, Das* das)
		{
			this->log = logger;
			this->das = das;
		}

		std::vector<Token> analizeFile(std::string fileName);
		std::vector<Token> analize(std::string text);
	};
}
