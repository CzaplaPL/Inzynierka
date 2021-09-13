#pragma once
#include <iostream>

#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/RegexException.h"
#include "PreviewElement.h"
#include <memory>

using namespace std;

class RegexConstructorSyntaxTree
{
	Logger* logger;
public:

	RegexConstructorSyntaxTree(Logger* logger)
	{
		this->logger = logger;
	}

protected:
	RegexNode*(RegexConstructorSyntaxTree::* checkAction(char &symbol))(char& firstChar, char& secondChar, shared_ptr<RegexNode>& tree);
	RegexNode* addOr(char& firstChar, char& secondChar, shared_ptr<RegexNode>&tree);
};
