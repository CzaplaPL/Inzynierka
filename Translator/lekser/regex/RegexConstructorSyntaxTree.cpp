#include "RegexConstructorSyntaxTree.h"

#include "RegexService.h"

RegexNode* (RegexConstructorSyntaxTree::* RegexConstructorSyntaxTree::checkAction(
	char& symbol))(PreviewElement previewElement, string& regex, RegexNode* tree)
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
	default:
		logger->info("return combine function");
		return &RegexConstructorSyntaxTree::addCombine;
	}
}

RegexNode* RegexConstructorSyntaxTree::addOr(PreviewElement previewElement, string& regex, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::OR);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addCombine(PreviewElement previewElement, string& regex, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::COMBINE);
	newTree->setSecondChild(RegexNodeType::ID, regex[0]);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addStar(PreviewElement previewElement, string& regex, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::STAR);
		return newTree;
	}
	newTree = new RegexNode(*tree, nullptr);
	RegexNode* newSecondChild(new RegexNode());
	newSecondChild->setType(RegexNodeType::STAR);
	newSecondChild->setFirstChild(secondChild);
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addPlus(PreviewElement previewElement, string& regex, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::PLUS);
		return newTree;
	}
	newTree = new RegexNode(*tree, nullptr);
	RegexNode* newSecondChild(new RegexNode());
	newSecondChild->setType(RegexNodeType::PLUS);
	newSecondChild->setFirstChild(secondChild);
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addQuestion(PreviewElement previewElement, string& regex, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::QUESTION);
		return newTree;
	}
	newTree = new RegexNode(*tree, nullptr);
	RegexNode* newSecondChild(new RegexNode());
	newSecondChild->setType(RegexNodeType::QUESTION);
	newSecondChild->setFirstChild(secondChild);
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addBrackets(PreviewElement previewElement, string& regex, RegexNode* tree)
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