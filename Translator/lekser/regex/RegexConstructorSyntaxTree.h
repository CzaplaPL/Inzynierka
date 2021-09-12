#pragma once
#include <iostream>

#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/RegexException.h"
#include "PreviewElement.h"

class RegexConstructorSyntaxTree
{
	Logger* logger;
public:

	RegexConstructorSyntaxTree(Logger* logger)
	{
		this->logger = logger;
	}

	int DoIt(float a, char b, char c) { cout << "TMyClass::DoIt" << endl; return a + b + c; };
	int DoMore(float a, char b, char c) const
	{
		cout << "TMyClass::DoMore" << endl; return a - b + c;
	};
	//protected:
	int (RegexConstructorSyntaxTree::* checkAction())(float a, char b, char c);
	//	void addOr(char& firstChar, char& secondChar, RegexNode* tree);
};
