#pragma once
#include <vector>
#include <unordered_set>

#include "Das.h"
#include "../regex/RegexNode.h"
#include "../sys/LekserException.h"
#include "../../addons/Logger.h"
#include "../Lekser.h"
#include "DasBuilder.h"
#include "../regex/RegexService.h"

class DasService
{
	Logger* log;
	RegexService regexService;
	DasBuilder dasBuilder;
	IdCreator idCreator;
public:
	DasService(Logger& logger) : regexService(logger), dasBuilder(logger)
	{
		this->log = &logger;
	}

	Das mergeDases(vector<Das>& dases);
	Lekser generateLekser(vector<pair<string, string>> elements);
};
