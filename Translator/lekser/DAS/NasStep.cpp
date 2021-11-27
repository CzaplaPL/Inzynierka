#include "NasStep.h"

NasStep::NasStep(vector<StepInDas> dasSteps, string stepId)
{
	this->stepId = stepId;
	this->dasSteps = dasSteps;
}

void NasStep::setAccepting(const string& token)
{
	this->isAccepting = true;
	this->token = token;
}