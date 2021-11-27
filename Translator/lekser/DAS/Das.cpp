#include "Das.h"

#include <stdexcept>

Das::Das(string token)
{
	this->token = token;
}

void Das::addStep(const string& stepId, const MachineStep& machineStep)
{
	if (this->steps.size() == 0)
	{
		firsStepId = stepId;
	}
	this->steps.insert_or_assign(stepId, machineStep);
}

bool Das::hasStep(const string& stepId)
{
	return this->steps.find(stepId) != this->steps.end();
}

MachineStep Das::getStep(string stepId)
{
	if (!hasStep(stepId))throw out_of_range("brak wskazanego kroku ");
	return this->steps[stepId];
}