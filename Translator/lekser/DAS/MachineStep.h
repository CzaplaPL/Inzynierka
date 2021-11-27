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
	string token;
	map<string, string> transitionsMap;
public:
	MachineStep(map<string, string>& transitions, bool isAccepting, string token = "");
	MachineStep();

	bool stepIsAccepting()
	{
		return this->isAccepting;
	}
	string getStepIdForString(string key);

	map<string, string> getTransitionsMap()
	{
		return this->transitionsMap;
	}
	string getAcceptingToken()
	{
		return token;
	}
};
