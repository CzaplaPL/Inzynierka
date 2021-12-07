#pragma once

#include "../addons/LoggerInterface.h"
#include "../addons/Logger.h"
#include "sys/LekserConfigReader.h"
class Lekser
{
	ILogger* log;
	//	LekserConfigReader configReader;
public:
	Lekser();
	Lekser(ILogger* log);
};
