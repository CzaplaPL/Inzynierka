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

Lex::RegexNode::RegexNode(RegexNode* tree, RegexNode* parent)
{
	this->type = tree->getType();
	this->blockId = tree->getBlockId();

	this->firstChild.reset(tree->getFirstChild());
	if (this->firstChild != nullptr) this->firstChild->setParents(this);
	this->secondChild.reset(tree->getSecondChild());
	if (this->secondChild != nullptr) this->secondChild->setParents(this);
	this->value = tree->getValue();
	this->parent.reset(parent);
	this->id = tree->getId();
}

Lex::RegexNode* Lex::RegexNode::operator[](int id)
{
	if (this->id == id)
	{
		return this;
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

Lex::RegexNode* Lex::RegexNode::getFirstChild()
{
	return this->firstChild.get();
}

Lex::RegexNode* Lex::RegexNode::getSecondChild()
{
	return secondChild.get();
}

Lex::RegexNode* Lex::RegexNode::getParent()
{
	return this->parent.get();
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

void Lex::RegexNode::setFirstChild(Lex::RegexNode* tree)
{
	tree->setParents(this);
	this->firstChild.reset( tree);
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

void Lex::RegexNode::setSecondChild(Lex::RegexNode* tree)
{
	tree->setParents(this);
	this->secondChild.reset(new RegexNode(tree, this));
}

void Lex::RegexNode::setParents(RegexNode* parent)
{
	this->parent.reset();
	this->parent.reset(parent);
}

std::string Lex::RegexNode::getValueAsString()
{
	if (this->type == RegexNodeType::BLOCK) return blockId;
	if (this->type == RegexNodeType::ID) return std::string(1, this->value);
	return "";
}