#pragma once

#include <vector>
#include <queue>

#include "Das.h"
#include "../sys/exception/LekserException.h"
#include "../addons/ILogger.h"
#include "../addons/IdCreator.h"
#include "../regex/RegexNode.h"
#include "MachineStep.h"
namespace Lex
{
	class DasBuilder
	{
		std::shared_ptr<ILogger> log;
		std::vector<int> checkFollowPos(RegexNode* parent);
		IdCreator idCreator;
	public:
		DasBuilder(std::shared_ptr<ILogger> log);

		std::vector<int> firstPos(RegexNode* tree);
		std::vector<int> followPos(RegexNode* tree);
		bool nullable(RegexNode* tree);
		Das generateDas(RegexNode* tree, std::string token);
	private:

		bool typeIsIdOrBlock(RegexNode* node);
	};
}