#pragma once
#include <map>
#include <set>
#include <vector>
#include <xstring>

using namespace std;

class MachineStep
{
	bool isAccepting;
	map<string, string> transitionsMap;
public:
	MachineStep(map<string, string>& transitions, bool isAccepting);
};
