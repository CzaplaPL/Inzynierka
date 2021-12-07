#pragma once
#include <vector>

#include"../../addons/LoggerInterface.h"
#include <fstream>

using namespace std;

class LekserConfigReader
{
	ILogger* log;
	vector<pair<string, string>> readData;
public:
	LekserConfigReader(ILogger& log);
	bool readConfig(fstream& file);
};
