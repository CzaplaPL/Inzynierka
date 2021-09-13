#include "RegexConstructorSyntaxTree.h"




shared_ptr<RegexNode> RegexConstructorSyntaxTree::addOr(char& firstChar, char& secondChar, shared_ptr<RegexNode>& tree)
{
	shared_ptr<RegexNode> newTree(new RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::OR);
	return newTree;
}


