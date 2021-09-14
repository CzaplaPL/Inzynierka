#include "RegexConstructorSyntaxTree.h"


RegexNode*(RegexConstructorSyntaxTree::* RegexConstructorSyntaxTree::checkAction(
	char& symbol))(char& firstChar, char& secondChar, RegexNode* tree)
{
	switch (symbol)
	{
	case '|':
		logger->info("return or function");
		return &RegexConstructorSyntaxTree::addOr;
		break;
	default:
		throw RegexException("nie znaleziono odpowiedniej funkcji");
		break;
	}
}

RegexNode* RegexConstructorSyntaxTree::addOr(char& firstChar, char& secondChar, RegexNode* tree)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::OR);
	return newTree;
}


