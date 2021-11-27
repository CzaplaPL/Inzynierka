#pragma once
#include <string>

class StepInDas
{
	int dasId;
	std::string stepId;
public:

	StepInDas(int dasId, std::string stepId);
	int getDasId();
	std::string getId();
};
