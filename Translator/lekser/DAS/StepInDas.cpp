#include "StepInDas.h"

StepInDas::StepInDas(int dasId, std::string stepId)
{
	this->stepId = stepId;
	this->dasId = dasId;
}

int StepInDas::getDasId()
{
	return this->dasId;
}

std::string StepInDas::getId()
{
	return this->stepId;
}