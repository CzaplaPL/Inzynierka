#pragma once
#include <string>

#include "RegexNodeType.h"

class PreviewElement
{
public:
	std::string value;
	RegexNodeType type;

	PreviewElement(char element);
	void setElement(char element);
	std::string toString();
};
