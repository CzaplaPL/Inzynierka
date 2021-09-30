#pragma once
#include <map>
#include <string>
#include "RegexNodeType.h"

using namespace std;

class RegexNode
{
	int id = -1;
	char value;
	string blockId;
	RegexNode* firstChild = nullptr;
	RegexNode* secondChild = nullptr;
	RegexNodeType type;
	RegexNode* parent = nullptr;

public:
	RegexNode();
	RegexNode(RegexNodeType type, char value, int id);
	RegexNode(RegexNode* tree, RegexNode* parent);
	RegexNode* operator[](int id);
	RegexNodeType getType();
	RegexNode* getFirstChild();
	RegexNode* getSecondChild();
	RegexNode* getParent();
	char getValue();
	string getBlockId();
	int getId();
	void setId(int id);
	void setValue(char value);
	void setBlockId(string& blockId);
	void setFirstChild(RegexNode* tree);
	void setType(RegexNodeType type);
	void setSecondChild(RegexNodeType type, char value, int id);
	void setSecondChild(RegexNode* tree);
	void setParents(RegexNode* parent);
	std::string toString();
	string getValueAsString();
};




