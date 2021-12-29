#include "RegexNode.h"

Lex::RegexNode::RegexNode()
{
}

Lex::RegexNode::RegexNode(RegexNodeType type, char value, int id)
{
	this->type = type;
	this->value = value;
	this->id = id;
}

Lex::RegexNode::RegexNode(std::shared_ptr < RegexNode> tree, std::shared_ptr < RegexNode> parent)
{
	this->type = tree->getType();
	this->blockId = tree->getBlockId();

	this->firstChild.reset(tree->getFirstChild().get());
	if (this->firstChild != nullptr) this->firstChild->setParents(this);
	this->secondChild.reset(tree->getSecondChild().get());
	if (this->secondChild != nullptr) this->secondChild->setParents(this);
	this->value = tree->getValue();
	this->parent = parent;
	this->id = tree->getId();
}

std::shared_ptr < Lex::RegexNode> Lex::RegexNode::operator[](int id)
{
	if (this->id == id)
	{
		return std::shared_ptr< RegexNode>(this);
	}
	if (this->id < id)
	{
		if (this->secondChild == nullptr) throw std::out_of_range("index poza zakresem");
		return (*this->secondChild)[id];
	}
	if (this->firstChild == nullptr) throw std::out_of_range("index poza zakresem");
	return (*this->firstChild)[id];
}

Lex::RegexNodeType Lex::RegexNode::getType()
{
	return this->type;
}

std::shared_ptr < Lex::RegexNode> Lex::RegexNode::getFirstChild()
{
	return this->firstChild;
}

std::shared_ptr < Lex::RegexNode> Lex::RegexNode::getSecondChild()
{
	return secondChild;
}

std::shared_ptr < Lex::RegexNode> Lex::RegexNode::getParent()
{
	return this->parent;
}

char Lex::RegexNode::getValue()
{
	return this->value;
}

std::string Lex::RegexNode::getBlockId()
{
	return this->blockId;
}

int Lex::RegexNode::getId()
{
	return this->id;
}

void Lex::RegexNode::setId(int id)
{
	this->id = id;
}

void Lex::RegexNode::setValue(char value)
{
	this->value = value;
}

void Lex::RegexNode::setBlockId(std::string& blockId)
{
	this->blockId = blockId;
}

void Lex::RegexNode::setFirstChild(std::shared_ptr < RegexNode> tree)
{
	tree->setParents(this);
	this->firstChild = tree;
}

void Lex::RegexNode::setType(RegexNodeType type)
{
	this->type = type;
}

void Lex::RegexNode::setSecondChild(RegexNodeType type, char value, int id)
{
	std::shared_ptr < RegexNode> secondChild(new RegexNode(type, value, id));
	secondChild->setParents(this);
	this->secondChild = secondChild;
}

void Lex::RegexNode::setSecondChild(std::shared_ptr < RegexNode> tree)
{
	tree->setParents(this);
	this->secondChild.reset(new RegexNode(tree, std::shared_ptr < RegexNode>(this)));
}

void Lex::RegexNode::setParents(RegexNode* parent)
{
	this->parent.reset(parent);
}

std::string Lex::RegexNode::getValueAsString()
{
	if (this->type == RegexNodeType::BLOCK) return blockId;
	if (this->type == RegexNodeType::ID) return std::string(1, this->value);
	return "";
}