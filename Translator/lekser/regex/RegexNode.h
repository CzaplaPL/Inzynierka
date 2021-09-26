#pragma once
#include <string>
#include "RegexNodeType.h"

using namespace std;

class RegexNode
{
	char value;
	string blockId;
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
	string getBlockId();
	void setValue(char value);
	void setBlockId(string& blockId);
	void setFirstChild(RegexNode* tree);
	void setType(RegexNodeType type);
	void setSecondChild(RegexNodeType type, char value);
	void setSecondChild(RegexNode* tree);
	std::string toString();
};
