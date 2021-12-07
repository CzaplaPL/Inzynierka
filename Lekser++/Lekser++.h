#pragma once

#include"addons/LoggerInterface.h"
#include"addons/Logger.h"

class __declspec(dllexport) Lekser
{
	ILogger* log;

public:
	Lekser();
	Lekser(ILogger* log);
};