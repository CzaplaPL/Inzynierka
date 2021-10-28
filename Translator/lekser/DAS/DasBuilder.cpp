#include "DasBuilder.h"

DasBuilder::DasBuilder(Logger& log)
{
	this->log = &log;
}

vector<int> DasBuilder::firstPos(RegexNode* tree)
{
	vector<int> toReturn;
	vector<int> secondFirstPos;
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

vector<int> DasBuilder::followPos(RegexNode* tree)
{
	if (tree == nullptr) throw LekserException("nie istnieje followPos dla pustego drzewa");
	RegexNode* parent = tree->getParent();
	vector<int> toReturn;
	vector<int> firstPosition;
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

bool DasBuilder::nullable(RegexNode* tree)
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
Das DasBuilder::generateDas(RegexNode* tree, string token)
{
	this->idCreator.clearMap();
	Das dasToReturn(token);
	queue<vector<int>> indefiniteStep;
	indefiniteStep.push(this->firstPos(tree));

	while (indefiniteStep.size() > 0)
	{
		vector<int> step = indefiniteStep.front();
		indefiniteStep.pop();
		map<string, set<int>> transitions;
		bool isAccepting = false;
		for (int nodeId : step)
		{
			RegexNode* node = (*tree)[nodeId];
			if (!typeIsIdOrBlock(node))throw LekserException("typ wezla jest inny niz block lub id");
			vector<int> followPosition = followPos(node);
			string value = node->getValueAsString();

			for (int position : followPosition)
			{
				transitions[value].insert(position);
			}
			if (node->getType() == RegexNodeType::END) isAccepting = true;
		}
		string stepId = this->idCreator.generateId(step);
		map <string, string> transitionWithId;
		for (pair<string, set<int>> transition : transitions)
		{
			vector<int> transitionSteps(transition.second.begin(), transition.second.end());
			string transitionStepId = this->idCreator.generateId(transitionSteps);
			if (!dasToReturn.hasStep(transitionStepId))
			{
				indefiniteStep.push(transitionSteps);
			}
			transitionWithId.insert_or_assign(transition.first, transitionStepId);
		}
		dasToReturn.addStep(stepId, MachineStep(transitionWithId, isAccepting));
	}
	return dasToReturn;
}

////////////////////funkcje prywatne////////////////////////////////////

vector<int> DasBuilder::checkFollowPos(RegexNode* parent)
{
	vector<int> toReturn;
	vector<int>  firstPosition;
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

bool DasBuilder::typeIsIdOrBlock(RegexNode* node)
{
	return (node->getType() == RegexNodeType::BLOCK || node->getType() == RegexNodeType::ID || node->getType() == RegexNodeType::END);
}