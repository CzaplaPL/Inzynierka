#include "DasServices.h"

vector<int> DasServices::firstPos(RegexNode* tree)
{
	vector<int> toReturn;
	vector<int> secondFirstPos;
	if(tree == nullptr) throw LekserException("nie istnieje firstpos dla pustego drzewa");
	switch (tree->getType())
	{
	case RegexNodeType::BLOCK:
	case RegexNodeType::ID:
		toReturn.push_back(tree->getId());
		return toReturn;
	case RegexNodeType::COMBINE:
		toReturn = firstPos(tree->getFirstChild());
		if(nullable(tree->getFirstChild()))
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

bool DasServices::nullable(RegexNode* tree)
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
