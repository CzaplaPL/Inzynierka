#pragma once
#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/RegexException.h"
#include "PreviewElement.h"
#include "RegexConstructorSyntaxTree.h"

class RegexService : private RegexConstructorSyntaxTree
{
	Logger* logger;
public:

	RegexService(Logger& logger) : RegexConstructorSyntaxTree(&logger)
	{
		this->logger = &logger;
	}

	RegexNode* generateTree(std::string& reg);
private:
};
