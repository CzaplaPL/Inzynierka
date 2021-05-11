#include "Logger.h"
#include <boost/filesystem.hpp>
#include <ctime>
#include <iostream>

Logger::Logger(string environment)
{
	this->isDebug = false;
	
	this->environment = environment;
	boost::filesystem::create_directory(environment);
	
	fileInfo.open("/log/" + environment + "/log-info.log", ios::trunc | ios::in | ios::out);
	fileLog.open("/log/" + environment + "/log.log", ios::trunc | ios::in | ios::out);
}

void Logger::setDebug(const bool isDebug)
{
	this->isDebug = isDebug;
}

void Logger::info(const string message)
{
	fileInfo << Logger::now()<< message << endl;
}

void Logger::debug(const string message)
{
	if(isDebug)
	{
		fileLog <<"[DEBUG] " << Logger::now() <<" "<< message << endl;
	}
}

void Logger::warning(const string message)
{
	fileLog << "[WARNING] " << Logger::now() << " " << message << endl;
}

void Logger::error(const string message)
{
	fileLog << "[ERROR] " << Logger::now() << " " << message << endl;
	cout << "\033[1;31m "<< "[ERROR] " << Logger::now() << " " << message << "\033[0m\n"<<endl;
}

string Logger::now()
{
	time_t rawtime ;
	struct tm timeinfo;
	char buffer[80];
	
	time(&rawtime);
	localtime_s(&timeinfo ,&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
	string str(buffer);
	
	return str;
}
