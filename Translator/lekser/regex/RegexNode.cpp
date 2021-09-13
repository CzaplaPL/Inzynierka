#include "RegexNode.h"

RegexNode::RegexNode()
{
}

RegexNode::RegexNode(RegexNode& tree, RegexNode* parent)
{
	this->type = tree.getType();
	this->firstChild.reset(tree.getFirstChild());
	this->firstChild.reset(tree.getSecondChild());
	this->value = tree.getValue();
	this->parent.reset(parent);
}

RegexNodeType RegexNode::getType()
{
	return this->type;
}

RegexNode* RegexNode::getFirstChild()
{
	return this->firstChild.get();
}

RegexNode* RegexNode::getSecondChild()
{
	return this->SecondChild.get();
}

char RegexNode::getValue()
{
	return this->value;
}

void RegexNode::setValue(char value)
{
	this->value = value;
}

void RegexNode::setFirstChild(const std::shared_ptr<RegexNode>& tree)
{
	this->firstChild.reset(new RegexNode(*tree,this));
}

void RegexNode::setType(RegexNodeType type)
{
	this->type = type;
}
