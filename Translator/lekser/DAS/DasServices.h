#pragma once
#include <vector>

#include "Das.h"
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
	string generateId(const vector<int>& vector);
	Das generateDas(RegexNode* tree);
};
