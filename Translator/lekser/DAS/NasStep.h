#pragma once
#include <string>
#include <vector>

#include "MachineStep.h"
#include "StepInDas.h"

using namespace std;
class NasStep
{
	string stepId;
	vector<StepInDas> dasSteps;
	map<string, StepInDas> transitions;
	bool isAccepting;
	string token;
public:
	NasStep(vector<StepInDas> dasSteps, string stepId);

	vector<StepInDas> getSteps()
	{
		return this->dasSteps;
	}

	void setAccepting(const string& token);

	string getStepId()
	{
		return this->stepId;
	}
};
