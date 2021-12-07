#pragma once
#include <cstdarg>
#include <ctime>
#include <direct.h>
#include <iostream>
#include <string>
#include <fstream>

#include "LoggerInterface.h"

using namespace std;

namespace Lex
{
	/// <summary>
	/// Klasa odpowiedzialna za zapisywanie danych do logów
	/// </summary>
	class  __declspec(dllexport) Logger : public ILogger
	{
		bool isDebug;
		bool isTime;
		fstream fileInfo;
		fstream fileLog;
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
		void writeStart(fstream& file) const;
		void close() noexcept;
	};
}
