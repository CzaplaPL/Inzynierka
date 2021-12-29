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
		std::shared_ptr < RegexNode> firstChild = nullptr;
		std::shared_ptr < RegexNode> secondChild = nullptr;
		RegexNodeType type = RegexNodeType::END;
		std::shared_ptr < RegexNode> parent = nullptr;

	public:
		RegexNode();
		RegexNode(RegexNodeType type, char value, int id);
		RegexNode(std::shared_ptr < RegexNode> tree, std::shared_ptr < RegexNode> parent);
		std::shared_ptr < RegexNode> operator[](int id);
		RegexNodeType getType();
		std::shared_ptr < RegexNode> getFirstChild();
		std::shared_ptr < RegexNode> getSecondChild();
		std::shared_ptr < RegexNode> getParent();
		char getValue();
		std::string getBlockId();
		int getId();
		void setId(int id);
		void setValue(char value);
		void setBlockId(std::string& blockId);
		void setFirstChild(std::shared_ptr < RegexNode> tree);
		void setType(RegexNodeType type);
		void setSecondChild(RegexNodeType type, char value, int id);
		void setSecondChild(std::shared_ptr < RegexNode> tree);
		void setParents(RegexNode* parent);
		std::string getValueAsString();
	};
}
