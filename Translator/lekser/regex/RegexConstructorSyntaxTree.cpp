#include "RegexConstructorSyntaxTree.h"

#include "RegexService.h"

RegexNode* (RegexConstructorSyntaxTree::* RegexConstructorSyntaxTree::checkAction(
	char& symbol))(PreviewElement previewElement, string& regex, RegexNode* tree, int& id)
{
	switch (symbol)
	{
	case '|':
		logger->info("return or function");
		return &RegexConstructorSyntaxTree::addOr;
	case '*':
		logger->info("return star function");
		return &RegexConstructorSyntaxTree::addStar;
	case '?':
		logger->info("return star function");
		return &RegexConstructorSyntaxTree::addQuestion;
	case '+':
		logger->info("return plus function");
		return &RegexConstructorSyntaxTree::addPlus;
	case '(':
		logger->info("return brackets function");
		return &RegexConstructorSyntaxTree::addBrackets;
	case '{':
		logger->info("return mustage brackets function");
		return &RegexConstructorSyntaxTree::addMustageBrackets;
	case '[':
		logger->info("return block function");
		return &RegexConstructorSyntaxTree::addBlock;
	default:
		logger->info("return combine function");
		return &RegexConstructorSyntaxTree::addCombine;
	}
}

RegexNode* RegexConstructorSyntaxTree::addOr(PreviewElement previewElement, string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::OR);
	newTree->setId(id);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addCombine(PreviewElement previewElement, string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::COMBINE);
	newTree->setId(id++);
	newTree->setSecondChild(RegexNodeType::ID, regex[0],id);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addStar(PreviewElement previewElement, string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr || tree->getType()==RegexNodeType::OR)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::STAR);
		newTree->setId(id);
		return newTree;
	}
	newTree = new RegexNode(*tree, nullptr);
	RegexNode* newSecondChild(new RegexNode());
	newSecondChild->setType(RegexNodeType::STAR);
	newSecondChild->setFirstChild(secondChild);
	newSecondChild->setId(id);
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addPlus(PreviewElement previewElement, string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr || tree->getType() == RegexNodeType::OR)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::PLUS);
		newTree->setId(id);
		return newTree;
	}
	newTree = new RegexNode(*tree, nullptr);
	RegexNode* newSecondChild(new RegexNode());
	newSecondChild->setType(RegexNodeType::PLUS);
	newSecondChild->setFirstChild(secondChild);
	newSecondChild->setId(id);
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addQuestion(PreviewElement previewElement, string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr || tree->getType() == RegexNodeType::OR)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::QUESTION);
		newTree->setId(id);
		return newTree;
	}
	newTree = new RegexNode(*tree, nullptr);
	RegexNode* newSecondChild(new RegexNode());
	newSecondChild->setType(RegexNodeType::QUESTION);
	newSecondChild->setFirstChild(secondChild);
	newSecondChild->setId(id);
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addBrackets(PreviewElement previewElement, string& regex, RegexNode* tree, int &id)
{
	RegexService regexService(*logger);
	regex.erase(0, 1);
	RegexNode* treeInBrackets(regexService.generateTree(regex));
	if (previewElement.type == RegexNodeType::OR)
	{
		tree->setSecondChild(treeInBrackets);
	}
	else
	{
		tree->setFirstChild(tree);
		tree->setType(RegexNodeType::COMBINE);
		tree->setSecondChild(treeInBrackets);
	}
	return new RegexNode(*tree);
}

RegexNode* RegexConstructorSyntaxTree::addMustageBrackets(PreviewElement previewElement, string& regex, RegexNode* tree, int &id)
{
	string element = previewElement.value;
	if (regex[1] == ',')
	{
		regex.erase(0, 2);
		int countChar = countCharLenght(regex);
		if (countChar < 1) throw LekserException("oczekiwano liczby dodatniej w wyra¿eniu {x,y}");

		RegexNode* newTree(new RegexNode());
		newTree = addQuestion(previewElement, regex, tree);
		for (int i = 1; i < countChar; ++i)
		{
			newTree = addCombine(previewElement, element, newTree);
			newTree = addQuestion(previewElement, regex, newTree);
		}
		regex.erase(0, 1);
		return newTree;
	}
	regex.erase(0, 1);
	int countChar = countCharLenght(regex);
	if (countChar < 1) throw LekserException("oczekiwano liczby dodatniej w wyra¿eniu {x,y}");
	RegexNode* newTree(new RegexNode(*tree));
	for (int i = 1; i < countChar; ++i)
	{
		newTree = addCombine(previewElement, element, newTree);
	}
	if (regex[0] == ',')
	{
		regex.erase(0, 1);
		int maxCountChar = countCharLenght(regex);
		if (maxCountChar == -1)
		{
			regex.erase(0, 1);
			newTree = addCombine(previewElement, element, newTree);
			newTree = addStar(previewElement, element, newTree);
			return newTree;
		}
		if (maxCountChar < 1) throw LekserException("oczekiwano liczby dodatniej w wyra¿eniu {x,y}");

		int countCharToExecute = maxCountChar - countChar;

		for (int i = 0; i < countCharToExecute; ++i)
		{
			newTree = addCombine(previewElement, element, newTree);
			newTree = addQuestion(previewElement, element, newTree);
		}
	}
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addBlock(PreviewElement previewElement, string& regex, RegexNode* tree, int &id)
{
	string index = "";
	int i = 1;
	for (;regex[i] != ']'; ++i)
	{
		if (i == regex.length()) throw LekserException("oczekiwano ]");
		index += regex[i];
	}
	if(index.length()<1)throw LekserException("brak wartoœci w bloku []");
	regex.erase(0, i);

	if(tree->getType() == RegexNodeType::BLOCK)
	{
		RegexNode* newTree(new RegexNode(*tree));
		newTree->setBlockId(index);
		return newTree;
	}
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::COMBINE);
	RegexNode* secondChild(new RegexNode);
	secondChild->setType(RegexNodeType::BLOCK);
	secondChild->setBlockId(index);
	newTree->setSecondChild(secondChild);
	return newTree;
}

int RegexConstructorSyntaxTree::countCharLenght(string& regex)
{
	string number = "";
	while (regex[0] != '}' && regex[0] != ',')
	{
		number += regex[0];
		regex.erase(0, 1);
	}
	if (number.length() < 1) return -1;
	return std::stoi(number);
}