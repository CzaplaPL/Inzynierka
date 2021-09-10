#pragma once
#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/RegexException.h"
#include "PreviewElement.h"



class RegexService
{
	Logger* logger;
public:

	RegexService(Logger& logger)
	{
		this->logger = &logger;
	}

	
	RegexNode* generateTree(std::string& reg);
private:
	void (RegexService::* checkAction(char value))();
	void myfun();
	void nofun();
	void addOr(char& firstChar, char& secondChar, RegexNode* tree);
};

