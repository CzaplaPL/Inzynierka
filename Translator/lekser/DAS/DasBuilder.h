#pragma once

#include <vector>
#include <queue>

#include "Das.h"
#include "../../addons/LekserException.h"
#include "../../addons/Logger.h"
#include "../regex/RegexNode.h"
#include "MachineStep.h"

class DasBuilder
{
	Logger* log;
	vector<int> checkFollowPos(RegexNode* parent);
public:
	DasBuilder(Logger& log);

	vector<int> firstPos(RegexNode* tree);
	vector<int> followPos(RegexNode* tree);
	bool nullable(RegexNode* tree);

	Das generateDas(RegexNode* tree);
private:
	string generateId(const vector<int>& vector);
	bool typeIsIdOrBlock(RegexNode* node);
};
