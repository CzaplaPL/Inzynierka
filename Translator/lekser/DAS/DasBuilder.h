#pragma once

#include <vector>
#include <queue>

#include "Das.h"
#include "../sys/LekserException.h"
#include "../../addons/Uuid.h"
#include "../../addons/Logger.h"
#include "../regex/RegexNode.h"
#include "MachineStep.h"

class DasBuilder
{
	Logger* log;
	vector<int> checkFollowPos(RegexNode* parent);
	map<string, string> stepIds;
public:
	DasBuilder(Logger& log);

	vector<int> firstPos(RegexNode* tree);
	vector<int> followPos(RegexNode* tree);
	bool nullable(RegexNode* tree);
	Das generateDas(RegexNode* tree, string token);
private:
	string generateId(const vector<int>& vector);
	bool typeIsIdOrBlock(RegexNode* node);
};
