#include "RegexNode.h"

RegexNodeType RegexNode::getType()
{
	return this->type;
}

RegexNode* RegexNode::getFirstChild()
{
	return this->firstChild;
}

RegexNode* RegexNode::getSecondChild()
{
	return this->SecondChild;
}

std::string RegexNode::getValue()
{
	return this->value;
}