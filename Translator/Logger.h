#pragma once

#include <string>
#include <fstream>

using namespace std;
/// <summary>
/// Klasa odpowiedzialna za zapisywanie danych do logów 
/// </summary>
class Logger
{
	bool isDebug;
	ofstream fileInfo;
	ofstream fileLog;
	string environment;
public:
	/// <param name="environment">srodowisko w jakim jest wykonywany program</param>
	Logger(string environment);

	/// <summary>
	/// ustawia tryb debugowania
	/// </summary>
	/// <param name="isDebug">informuje czy tryb debugowania jest uruchomiony</param>
	void setDebug(bool isDebug);

	
	void info(string message);
	void debug(string message);
	void warning(string message);
	void error(string message);
private:
	static string now();
};

