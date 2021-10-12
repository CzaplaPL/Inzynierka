#include "DasService.h"

#include <map>
#include <queue>
#include <set>

#include "MachineStep.h"

//todo logi

vector<int> DasService::firstPos(RegexNode* tree)
{
	vector<int> toReturn;
	vector<int> secondFirstPos;
	if (tree == nullptr) throw LekserException("nie istnieje firstpos dla pustego drzewa");
	switch (tree->getType())
	{
	case RegexNodeType::BLOCK:
	case RegexNodeType::END:
	case RegexNodeType::ID:
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

vector<int> DasService::followPos(RegexNode* tree)
{
	if (tree == nullptr) throw LekserException("nie istnieje followPos dla pustego drzewa");
	RegexNode* parent = tree->getParent();
	vector<int> toReturn;
	vector<int> firstPosition;
	RegexNode* actualParent;
	if (parent == nullptr) return toReturn;

	switch (parent->getType())
	{
	case RegexNodeType::OR:
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

bool DasService::nullable(RegexNode* tree)
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
		return true;
	}
}

Das DasService::generateDas(RegexNode* tree)
{
	Das toReturn;
	queue<vector<int>> indefiniteStep;
	map<string, MachineStep> machineSteps;
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
			if (node->getType() == RegexNodeType::END)isAccepting = true;
		}
		string stepId = generateId(step);
		machineSteps.insert({ stepId,MachineStep(transitions,isAccepting) });
		for (pair< string, set<int>> transition : transitions)
		{
			vector<int> transitionSteps(transition.second.begin(), transition.second.end());
			if (machineSteps.find(generateId(transitionSteps)) == machineSteps.end()) {
				indefiniteStep.push(transitionSteps);
			}
		}
	}

	for (pair< string, MachineStep> el : machineSteps)
	{
		int c = 0;
	}
	return toReturn;
}

string DasService::generateId(const vector<int>& vector)
{
	string toReturn = "";
	for (int element : vector)
	{
		toReturn += to_string(element) + "-";
	}
	return toReturn;
}

vector<int> DasService::checkFollowPos(RegexNode* parent)
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
			firstPosition = firstPos(actualParent->getSecondChild());
			toReturn.insert(toReturn.end(), firstPosition.begin(), firstPosition.end());
			return toReturn;
		case RegexNodeType::PLUS:
		case RegexNodeType::STAR:
			firstPosition = firstPos(actualParent->getFirstChild());
			toReturn.insert(toReturn.end(), firstPosition.begin(), firstPosition.end());
			actualParent = actualParent->getParent();
			break;
		}
	}
}

bool DasService::typeIsIdOrBlock(RegexNode* node)
{
	return (node->getType() == RegexNodeType::BLOCK || node->getType() == RegexNodeType::ID || node->getType() == RegexNodeType::END);
}