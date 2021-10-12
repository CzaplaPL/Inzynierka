#include "MachineStep.h"

MachineStep::MachineStep(map<string, set<int>>& transitions, bool isAccepting) :transitionsMap(transitions)
{
	this->isAccepting = isAccepting;
}