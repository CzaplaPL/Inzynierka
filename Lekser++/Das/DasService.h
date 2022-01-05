#pragma once
#include <vector>
#include <unordered_set>

#include "Das.h"
#include "NasStep.h"
#include "StepInDas.h"
#include "../regex/RegexNode.h"
#include "../sys/exception/LekserException.h"
#include "../addons/ILogger.h"
#include "DasBuilder.h"
#include "../regex/Services/RegexService.h"

namespace Lex
{
	class DasService
	{
		ILogger* log;
		RegexService regexService;
		DasBuilder dasBuilder;
		IdCreator idCreator;
	public:
		DasService(ILogger& logger) : regexService(logger), dasBuilder(logger)
		{
			this->log = &logger;
		}

		Das mergeDases(std::vector<Das>& dases);
		void generateLekser(std::vector< std::pair< std::string, std::string>> elements);
	};
}