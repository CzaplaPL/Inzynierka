#pragma once
#include <string>
#include "RegexNodeType.h"

class RegexNode
{
	char value;
	RegexNode* firstChild = nullptr;
	RegexNode* secondChild = nullptr;
	RegexNodeType type;
	RegexNode* parent = nullptr;

public:
	RegexNode();
	RegexNode(RegexNodeType type, char value);
	RegexNode(RegexNode& tree, RegexNode* parent);
	RegexNodeType getType();
	RegexNode* getFirstChild();
	RegexNode* getSecondChild();
	char getValue();
	void setValue(char value);
	void setFirstChild(RegexNode* tree);
	void setType(RegexNodeType type);
	void setSecondChild(RegexNodeType type, char value);
	void setSecondChild(RegexNode* tree);
	std::string toString();
};
