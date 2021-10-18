#pragma once
#include <map>
#include <set>
#include <vector>
#include <xstring>

#include "../sys/NoStepException.h"

using namespace std;

class MachineStep
{
	bool isAccepting;
	map<string, string> transitionsMap;
public:
	MachineStep(map<string, string>& transitions, bool isAccepting);
	MachineStep();

	bool stepIsAccepting()
	{
		return this->isAccepting;
	}
	string getStepIdForString(string key);
};
