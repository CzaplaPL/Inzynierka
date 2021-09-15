#include "RegexConstructorSyntaxTree.h"

RegexNode* (RegexConstructorSyntaxTree::* RegexConstructorSyntaxTree::checkAction(
	char& symbol))(PreviewElement previewElement, char& curentElement, RegexNode* tree)
{
	switch (symbol)
	{
	case '|':
		logger->info("return or function");
		return &RegexConstructorSyntaxTree::addOr;
	case '*':
		logger->info("return star function");
		return &RegexConstructorSyntaxTree::addStar;
	case '+':
		logger->info("return plus function");
		return &RegexConstructorSyntaxTree::addPlus;
	default:
		logger->info("return combine function");
		return &RegexConstructorSyntaxTree::addCombine;
	}
}

RegexNode* RegexConstructorSyntaxTree::addOr(PreviewElement previewElement, char& curentElement, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::OR);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addCombine(PreviewElement previewElement, char& curentElement, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::COMBINE);
	newTree->setSecondChild(RegexNodeType::ID, curentElement);
	return newTree;
}

RegexNode* RegexConstructorSyntaxTree::addStar(PreviewElement previewElement, char& curentElement, RegexNode* tree)
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

RegexNode* RegexConstructorSyntaxTree::addPlus(PreviewElement previewElement, char& curentElement, RegexNode* tree)
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