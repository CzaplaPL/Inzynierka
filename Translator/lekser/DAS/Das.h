#pragma once
#include "MachineStep.h"

class Das
{
	map<string, MachineStep> steps;
public:
	void addStep(const string& stepId, const MachineStep& machineStep);

	bool hasStep(const string& stepId);
};
