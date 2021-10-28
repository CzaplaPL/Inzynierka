#pragma once
#include <vector>

#include "Das.h"
#include "../regex/RegexNode.h"
#include "../sys/LekserException.h"
#include "../../addons/Logger.h"
#include "../Lekser.h"
#include "DasBuilder.h"
#include "../regex/RegexService.h"

class DasServices
{
	Logger* log;
	RegexService regexService;
	DasBuilder dasBuilder;

public:
	DasServices(Logger& logger) : regexService(logger), dasBuilder(logger)
	{
		this->log = &logger;
	}

	Das mergeDases(const vector<Das>& dases);
	Lekser generateLekser(vector<pair<string, string>> elements);
};
