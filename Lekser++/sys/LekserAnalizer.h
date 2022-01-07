#pragma once
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "../addons/ILogger.h"
#include "../Das/Das.h"
#include "exception/NoStepException.h"

namespace Lex
{
	class LekserAnalizer
	{
		std::shared_ptr<ILogger> log;
		Das* das;
		std::vector<std::string> analizeLine(std::string line);
	public:
		LekserAnalizer(std::shared_ptr<ILogger> logger, Das* das)
		{
			this->log = logger;
			this->das = das;
		}

		std::vector<std::string> analizeFile(std::string fileName);
	};
}