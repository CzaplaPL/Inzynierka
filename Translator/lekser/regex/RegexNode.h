#pragma once
#include <string>

#include "RegexNodeType.h"

class RegexNode
{
	std::string value;
	RegexNode* firstChild = nullptr;
	RegexNode* SecondChild = nullptr;
	RegexNodeType type;
	RegexNode* parent;

public:
	RegexNodeType getType();
	RegexNode* getFirstChild();
	RegexNode* getSecondChild();
	std::string getValue();
};
