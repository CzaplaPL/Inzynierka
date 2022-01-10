#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>

#include "RegexNodeType.h"

namespace Lex
{
	/// <summary>
	/// weze³ w drzewie rozbioru
	/// </summary>
	class RegexNode
	{
		int id = -1;
		char value;
		std::string blockId;
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
		std::string getBlockId();
		int getId();
		void setId(int id);
		void setValue(char value);
		void setBlockId(std::string& blockId);
		void setFirstChild(RegexNode* tree);
		void setType(RegexNodeType type);
		void setSecondChild(RegexNodeType type, char value, int id);
		void setSecondChild(RegexNode* tree);
		void setParents(RegexNode* parent);
		std::string getValueAsString();
		~RegexNode();
	};
}
