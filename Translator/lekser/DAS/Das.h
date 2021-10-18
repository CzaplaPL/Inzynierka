#pragma once
#include "MachineStep.h"

class Das
{
	string token;
	string firsStepId;
	map<string, MachineStep> steps;
public:
	Das(string token);

	void addStep(const string& stepId, const MachineStep& machineStep);

	bool hasStep(const string& stepId);

	string getToken()
	{
		return this->token;
	}
	string getFirstStepId()
	{
		return this->firsStepId;
	}
	MachineStep getStep(string stepId);
	int getStepSize()
	{
		return steps.size();
	}
};
