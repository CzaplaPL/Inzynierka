#pragma once
#include "../Translator/lekser/regex/RegexNode.h"

class RegexServices
{
public:
	RegexNode generateTree(std::string reg);
};

