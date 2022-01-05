#include "NasStep.h"

Lex::NasStep::NasStep(std::vector<StepInDas> dasSteps, std::string stepId)
{
	this->stepId = stepId;
	this->dasSteps = dasSteps;
}

void Lex::NasStep::setAccepting(const std::string& token)
{
	this->isAccepting = true;
	this->token = token;
}