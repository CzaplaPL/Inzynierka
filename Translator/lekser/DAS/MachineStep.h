#pragma once
#include <vector>

using namespace std;

class MachineStep
{
	vector<int> nodes;
public:
	MachineStep(const vector<int>& positions);

	void setNodes(vector<int> nodes)
	{
		this->nodes = nodes;
	}
	vector<int>getNodes()
	{
		return this->nodes;
	}
};
