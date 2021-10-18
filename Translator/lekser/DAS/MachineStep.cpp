#include "MachineStep.h"

MachineStep::MachineStep(map<string, string>& transitions, bool isAccepting) :transitionsMap(transitions)
{
	this->isAccepting = isAccepting;
}