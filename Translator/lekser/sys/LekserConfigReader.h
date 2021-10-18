#pragma once
#include <vector>

#include "../Translator/addons/Logger.h"

class LekserConfigReader
{
	Logger* log;
	vector<pair<string, string>> readData;
public:
	LekserConfigReader(Logger& log);
	bool readConfig(fstream& file);
};
