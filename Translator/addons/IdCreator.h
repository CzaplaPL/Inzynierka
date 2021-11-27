#pragma once
#include <map>
#include <string>
#include <vector>
#include "Uuid.h"

using namespace std;
class IdCreator
{
	map<string, string> stepIds;
public:
	void clearMap();
	string generateId(const vector<int>& vector);
	string generateId(const vector<std::string>& vector);
};
