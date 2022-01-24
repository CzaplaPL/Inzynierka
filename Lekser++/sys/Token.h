#pragma once
#include <string>

class __declspec(dllexport) Token
{
public:
	std::string name;
	std::string value;
	Token(std::string name, std::string value)
	{
		this->name = name;
		this->value = value;
	}
};
