#pragma once
#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/RegexException.h"

class RegexServices
{
	Logger* logger;
public:

	RegexServices(Logger& logger)
	{
		this->logger = &logger;
	}

	RegexNode* generateTree(std::string& reg);
private:

	void addOr(char& firstChar, char& secondChar, RegexNode* tree);
};
