#pragma once

#include <vector>
#include <queue>

#include "Das.h"
#include "../sys/LekserException.h"
#include "../../addons/Uuid.h"
#include "../../addons/Logger.h"
#include "../../addons/IdCreator.h"
#include "../regex/RegexNode.h"
#include "MachineStep.h"

class DasBuilder
{
	Logger* log;
	vector<int> checkFollowPos(RegexNode* parent);
	IdCreator idCreator;
public:
	DasBuilder(Logger& log);

	vector<int> firstPos(RegexNode* tree);
	vector<int> followPos(RegexNode* tree);
	bool nullable(RegexNode* tree);
	Das generateDas(RegexNode* tree, string token);
private:

	bool typeIsIdOrBlock(RegexNode* node);
};
