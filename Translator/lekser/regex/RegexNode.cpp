#include "RegexNode.h"
#include "RegexService.h"

RegexNode::RegexNode()
{
}

RegexNode::RegexNode(RegexNodeType type, char value)
{
	this->type = type;
	this->value = value;
}

RegexNode::RegexNode(RegexNode& tree, RegexNode* parent)
{
	this->type = tree.getType();

	this->firstChild = tree.getFirstChild();

	this->secondChild = tree.getSecondChild();

	this->value = tree.getValue();
	this->parent = parent;
}

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
	return secondChild;
}

char RegexNode::getValue()
{
	return this->value;
}

void RegexNode::setValue(char value)
{
	this->value = value;
}

void RegexNode::setFirstChild(RegexNode* tree)
{
	this->firstChild = new RegexNode(*tree, this);
}

void RegexNode::setType(RegexNodeType type)
{
	this->type = type;
}

void RegexNode::setSecondChild(RegexNodeType type, char value)
{
	this->secondChild = new RegexNode(type, value);
}

void RegexNode::setSecondChild(RegexNode* tree)
{
	this->secondChild = new RegexNode(*tree, this);
}

std::string RegexNode::toString()
{
	std::string toReturn = "Regex node: \n";
	toReturn += "value = " + std::string(1, value) + "\n";
	toReturn += "type = " + RegexService::regexNodeTypeToString(type) + "\n";

	if (firstChild != nullptr)
	{
		toReturn += "firsChild:" + firstChild->toString() + "\n";
	}
	else
	{
		toReturn += "firsChild = NULL \n";
	}
	if (secondChild != nullptr)
	{
		toReturn += "secondChild:" + secondChild->toString();
	}
	else
	{
		toReturn += "secondChild = NULL";
	}

	return toReturn;
}