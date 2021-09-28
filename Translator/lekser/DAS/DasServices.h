#pragma once
#include <vector>
#include "../regex/RegexNode.h"
#include "../../addons/LekserException.h"
#include "../../addons/Logger.h"

class DasServices
{
	Logger* log;
public:
	DasServices(Logger& logger)
	{
		this->log = &logger;
	}
	vector<int> firstPos(RegexNode* tree);
	bool nullable(RegexNode* tree);
};

