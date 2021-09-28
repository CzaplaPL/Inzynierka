#include "RegexNode.h"
#include "RegexService.h"

RegexNode::RegexNode()
{
}

RegexNode::RegexNode(RegexNodeType type, char value, int id)
{
	this->type = type;
	this->value = value;
	this->id = id;
}

RegexNode::RegexNode(RegexNode& tree, RegexNode* parent)
{
	this->type = tree.getType();

	this->blockId = tree.getBlockId();

	this->firstChild = tree.getFirstChild();

	this->secondChild = tree.getSecondChild();

	this->value = tree.getValue();
	this->parent = parent;
	this->id = tree.getId();
}

RegexNode& RegexNode::operator[](int id)
{
	if (this->id == id)
	{
		return *this;
	}
	if (this->id < id)
	{
		if (this->secondChild == nullptr) throw LekserException("index poza zakresem");
		return (*this->secondChild)[id];
	}
	if (this->firstChild == nullptr) throw LekserException("index poza zakresem");
	return (*this->firstChild)[id];
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

std::string RegexNode::getBlockId()
{
	return this->blockId;
}

int RegexNode::getId()
{
	return this->id;
}

void RegexNode::setId(int id)
{
	this->id = id;
}

void RegexNode::setValue(char value)
{
	this->value = value;
}

void RegexNode::setBlockId(std::string& blockId)
{
	this->blockId = blockId;
}

void RegexNode::setFirstChild(RegexNode* tree)
{
	this->firstChild = new RegexNode(*tree, this);
}

void RegexNode::setType(RegexNodeType type)
{
	this->type = type;
}

void RegexNode::setSecondChild(RegexNodeType type, char value, int id)
{
	this->secondChild = new RegexNode(type, value, id);
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