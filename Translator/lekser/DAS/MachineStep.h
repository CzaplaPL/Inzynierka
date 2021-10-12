#pragma once
#include <map>
#include <set>
#include <vector>
#include <xstring>

using namespace std;

class MachineStep
{
	map<string, set<int>> transitionsMap;
public:
	MachineStep(map<string, set<int>>& transitions);
};
