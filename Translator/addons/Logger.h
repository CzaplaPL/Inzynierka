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
	bool isTime;
	ofstream fileInfo;
	ofstream fileLog;
	string environment;
public:
	static const string VERSION;

	/// <param name="environment">srodowisko w jakim jest wykonywany program</param>
	Logger(string environment);

	~Logger();
	/// <summary>
	/// ustawia tryb debugowania
	/// </summary>
	/// <param name="isDebug">informuje czy tryb debugowania jest uruchomiony</param>
	void setDebug(bool isDebug) noexcept;

	/// <summary>
	/// ustawia czy ma byc wyœwietlany czas
	/// </summary>
	/// <param name="isTime"></param>
	void setTime(bool isTime)  noexcept;

	void info(string message);
	void debug(string message);
	void warning(string message);
	void error(string message);
	void writeDebug(const char* templates, ...);
private:
	string now() const;
	void writeStart(ofstream& file) const;
	void close() noexcept;
};
