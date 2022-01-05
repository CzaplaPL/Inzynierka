#include "DasBuilder.h"

Lex::DasBuilder::DasBuilder(ILogger& log)
{
	this->log = &log;
}

std::vector<int> Lex::DasBuilder::firstPos(RegexNode* tree)
{
	std::vector<int> toReturn;
	std::vector<int> secondFirstPos;
	if (tree == nullptr) throw LekserException("nie istnieje firstpos dla pustego drzewa");
	switch (tree->getType())
	{
	case RegexNodeType::BLOCK:
	case RegexNodeType::ID:
	case RegexNodeType::END:
		toReturn.push_back(tree->getId());
		return toReturn;
	case RegexNodeType::COMBINE:
		toReturn = firstPos(tree->getFirstChild());
		if (nullable(tree->getFirstChild()))
		{
			secondFirstPos = firstPos(tree->getSecondChild());
			toReturn.insert(toReturn.end(), secondFirstPos.begin(), secondFirstPos.end());
		}
		return toReturn;
	case RegexNodeType::OR:
		toReturn = firstPos(tree->getFirstChild());
		secondFirstPos = firstPos(tree->getSecondChild());
		toReturn.insert(toReturn.end(), secondFirstPos.begin(), secondFirstPos.end());
		return toReturn;
	case RegexNodeType::PLUS:
	case RegexNodeType::STAR:
	case RegexNodeType::QUESTION:
		toReturn = firstPos(tree->getFirstChild());
		return toReturn;

	default:
		throw LekserException("nie znaleziono firstPos");
	}
}

std::vector<int> Lex::DasBuilder::followPos(RegexNode* tree)
{
	if (tree == nullptr) throw LekserException("nie istnieje followPos dla pustego drzewa");
	RegexNode* parent = tree->getParent();
	std::vector<int> toReturn;
	std::vector<int> firstPosition;
	if (parent == nullptr) return toReturn;

	switch (parent->getType())
	{
	case RegexNodeType::OR:
	case RegexNodeType::QUESTION:
		return  checkFollowPos(parent);
	case RegexNodeType::PLUS:
	case RegexNodeType::STAR:
		toReturn.push_back(tree->getId());
		firstPosition = checkFollowPos(parent);
		toReturn.insert(toReturn.end(), firstPosition.begin(), firstPosition.end());
		return toReturn;
	case RegexNodeType::COMBINE:
		if (tree->getId() == parent->getSecondChild()->getId())return checkFollowPos(parent);
		return firstPos(parent->getSecondChild());
	}
	return toReturn;
}

bool Lex::DasBuilder::nullable(RegexNode* tree)
{
	switch (tree->getType())
	{
	case RegexNodeType::BLOCK:
	case RegexNodeType::ID:
		return false;
	case RegexNodeType::COMBINE:
		return nullable(tree->getFirstChild()) && nullable(tree->getSecondChild());
	case RegexNodeType::OR:
		return nullable(tree->getFirstChild()) || nullable(tree->getSecondChild());
	case RegexNodeType::PLUS:
		return nullable(tree->getFirstChild());
	case RegexNodeType::QUESTION:
	case RegexNodeType::STAR:
	case RegexNodeType::END:
		return true;
	}
}

/// todo logi
///	todo cashe
///	todo set to vectorSet
Lex::Das Lex::DasBuilder::generateDas(RegexNode* tree, std::string token)
{
	this->idCreator.clearMap();
	Das dasToReturn;
	std::queue<std::vector<int>> indefiniteStep;
	indefiniteStep.push(this->firstPos(tree));

	while (indefiniteStep.size() > 0)
	{
		std::vector<int> step = indefiniteStep.front();
		indefiniteStep.pop();
		std::map<std::string, std::set<int>> transitions;
		bool isAccepting = false;
		for (int nodeId : step)
		{
			RegexNode* node = (*tree)[nodeId];
			if (!typeIsIdOrBlock(node))throw LekserException("typ wezla jest inny niz block lub id");
			std::vector<int> followPosition = followPos(node);
			std::string value = node->getValueAsString();

			for (int position : followPosition)
			{
				transitions[value].insert(position);
			}
			if (node->getType() == RegexNodeType::END) isAccepting = true;
		}
		std::string stepId = this->idCreator.generateId(step);
		std::map <std::string, std::string> transitionWithId;
		for (std::pair<std::string, std::set<int>> transition : transitions)
		{
			std::vector<int> transitionSteps(transition.second.begin(), transition.second.end());
			std::string transitionStepId = this->idCreator.generateId(transitionSteps);
			if (!dasToReturn.hasStep(transitionStepId))
			{
				indefiniteStep.push(transitionSteps);
			}
			transitionWithId.insert_or_assign(transition.first, transitionStepId);
		}
		dasToReturn.addStep(stepId, MachineStep(transitionWithId, isAccepting, token));
	}
	return dasToReturn;
}

////////////////////funkcje prywatne////////////////////////////////////

std::vector<int> Lex::DasBuilder::checkFollowPos(RegexNode* parent)
{
	std::vector<int> toReturn;
	std::vector<int>  firstPosition;
	RegexNode* actualParent = parent->getParent();
	while (true)
	{
		if (actualParent == nullptr) return toReturn;
		switch (actualParent->getType())
		{
		case RegexNodeType::QUESTION:
		case RegexNodeType::OR:
			actualParent = actualParent->getParent();
			break;
		case RegexNodeType::COMBINE:
			if (parent->getId() == actualParent->getSecondChild()->getId())
			{
				actualParent = actualParent->getParent();
				break;
			}
			firstPosition = firstPos(actualParent->getSecondChild());
			toReturn.insert(toReturn.end(), firstPosition.begin(), firstPosition.end());
			if (nullable(actualParent->getSecondChild()))
			{
				actualParent = actualParent->getParent();
				break;
			}
			return toReturn;
		case RegexNodeType::PLUS:
		case RegexNodeType::STAR:
			firstPosition = firstPos(actualParent->getFirstChild());
			toReturn.insert(toReturn.end(), firstPosition.begin(), firstPosition.end());
			actualParent = actualParent->getParent();
			break;
		case RegexNodeType::ID:
		case RegexNodeType::BLOCK:
		case RegexNodeType::END:
		default:
			throw LekserException("nie mo¿na wywo³aæ funkcji checkFollowPos dla ID,block i end");
		}
	}
}

bool Lex::DasBuilder::typeIsIdOrBlock(RegexNode* node)
{
	return (node->getType() == RegexNodeType::BLOCK || node->getType() == RegexNodeType::ID || node->getType() == RegexNodeType::END);
}