#pragma once

#include <vector>
#include <unordered_set>

#include "Das.h"
#include "NasStep.h"
#include "StepInDas.h"
#include "../regex/RegexNode.h"
#include "../sys/exception/LekserException.h"
#include "../sys/Rule.h"
#include "../addons/ILogger.h"
#include "DasBuilder.h"
#include "../regex/Services/RegexService.h"

namespace Lex
{
	class DasService
	{
		std::shared_ptr<ILogger> log;
		RegexService regexService;
		DasBuilder dasBuilder;
		IdCreator idCreator;
	public:
		DasService(std::shared_ptr<ILogger> logger) : regexService(logger), dasBuilder(logger)
		{
			this->log = logger;
		}

		Das mergeDases(std::vector<Das>& dases);
		Das generateLekser(std::vector<Lex::Rule> elements);

		~DasService()
		{
			this->log.reset();
		}
	};
}