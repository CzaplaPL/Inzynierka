#pragma once
#include <string>
#include <memory>
#include "RegexNodeType.h"

class RegexNode
{
	char value;
	std::unique_ptr<RegexNode> firstChild;
	std::unique_ptr<RegexNode> secondChild;
	RegexNodeType type;
	std::unique_ptr<RegexNode> parent;

public:
	RegexNode();
	RegexNode(RegexNodeType type, char value);
	RegexNode(RegexNode& tree, RegexNode* parent);
	RegexNodeType getType();
	RegexNode* getFirstChild();
	RegexNode* getSecondChild();
	char getValue();
	void setValue(char value);
	void setFirstChild(const std::shared_ptr<RegexNode>& tree);
	void setType(RegexNodeType type);
	void setSecondChild(RegexNodeType type, char value);
	std::string toString();
};
