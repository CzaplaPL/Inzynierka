#pragma once
#include <vector>

#include "Das.h"
#include "../regex/RegexNode.h"
#include "../../addons/LekserException.h"
#include "../../addons/Logger.h"

class DasServices
{
	Logger* log;
	vector<int> checkFollowPos(RegexNode* parent);
public:
	DasServices(Logger& logger)
	{
		this->log = &logger;
	}
	vector<int> firstPos(RegexNode* tree);

	vector<int> followPos(RegexNode* tree);
	bool nullable(RegexNode* tree);
	string generateId(const vector<int>& vector);
	bool typeIsIdOrBlock(RegexNode* node);
	Das generateDas(RegexNode* tree);
};
