#include "MachineStep.h"

MachineStep::MachineStep(map<string, string>& transitions, bool isAccepting, string token) :transitionsMap(transitions)
{
	this->isAccepting = isAccepting;
	this->token = token;
}

MachineStep::MachineStep()
{
	this->isAccepting = false;
}

string MachineStep::getStepIdForString(string key)
{
	if (this->transitionsMap.find(key) == this->transitionsMap.end())throw NoStepException("brak wskazanego kroku dla " + key);
	return this->transitionsMap[key];
}