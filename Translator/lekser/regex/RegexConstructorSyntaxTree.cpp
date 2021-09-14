#include "RegexConstructorSyntaxTree.h"

RegexNode* (RegexConstructorSyntaxTree::* RegexConstructorSyntaxTree::checkAction(
	char& symbol))(PreviewElement previewElement, char& curentElement, RegexNode* tree)
{
	switch (symbol)
	{
	case '|':
		logger->info("return or function");
		return &RegexConstructorSyntaxTree::addOr;
		break;
	default:
		logger->info("return combine function");
		return &RegexConstructorSyntaxTree::addCombine;
		break;
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