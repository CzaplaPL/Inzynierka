#include "MachineStep.h"

Lex::MachineStep::MachineStep(std::map<std::string, std::string>& transitions, bool isAccepting, std::string token) :transitionsMap(transitions)
{
	this->isAccepting = isAccepting;
	this->token = token;
}

Lex::MachineStep::MachineStep()
{
	this->isAccepting = false;
}

std::string Lex::MachineStep::getStepIdForString(std::string key)
{
	if (this->transitionsMap.find(key) == this->transitionsMap.end())throw NoStepException("brak wskazanego kroku dla " + key);
	return this->transitionsMap[key];
}