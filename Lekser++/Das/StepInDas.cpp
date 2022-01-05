#include "StepInDas.h"

Lex::StepInDas::StepInDas(int dasId, std::string stepId)
{
	this->stepId = stepId;
	this->dasId = dasId;
}

int Lex::StepInDas::getDasId()
{
	return this->dasId;
}

std::string Lex::StepInDas::getId()
{
	return this->stepId;
}