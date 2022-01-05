#include "Das.h"

void Lex::Das::addStep(const std::string& stepId, const MachineStep& machineStep)
{
	if (this->steps.size() == 0)
	{
		firsStepId = stepId;
	}
	this->steps.insert_or_assign(stepId, machineStep);
}

bool Lex::Das::hasStep(const std::string& stepId)
{
	return this->steps.find(stepId) != this->steps.end();
}

Lex::MachineStep Lex::Das::getStep(std::string stepId)
{
	if (!hasStep(stepId))throw std::out_of_range("brak wskazanego kroku ");
	return this->steps[stepId];
}