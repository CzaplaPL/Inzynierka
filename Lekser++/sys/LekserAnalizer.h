#pragma once
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "../addons/ILogger.h"

namespace Lex
{
	class LekserAnalizer
	{
		std::shared_ptr<ILogger> log;
	public:
		LekserAnalizer(std::shared_ptr<ILogger> logger)
		{
			this->log = logger;
		}

		std::vector<std::string> analizeFile(std::string fileName);
	};
}
