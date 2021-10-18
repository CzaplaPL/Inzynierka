#include "Das.h"

void Das::addStep(const string& stepId, const MachineStep& machineStep)
{
	this->steps.insert_or_assign(stepId, machineStep);
}

bool Das::hasStep(const string& stepId)
{
	return this->steps.find(stepId) != this->steps.end();
}