#include "RegexConstructorSyntaxTree.h"


RegexNode*(RegexConstructorSyntaxTree::* RegexConstructorSyntaxTree::checkAction(
	char& symbol))(char& firstChar, char& secondChar, shared_ptr<RegexNode>& tree)
{
	switch (symbol)
	{
	case '|':
		logger->info("return or function");
		return &RegexConstructorSyntaxTree::addOr;
		break;
	}
}

RegexNode* RegexConstructorSyntaxTree::addOr(char& firstChar, char& secondChar, std::shared_ptr<RegexNode>& tree)
{
	RegexNode* newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::OR);
	return newTree;
}


