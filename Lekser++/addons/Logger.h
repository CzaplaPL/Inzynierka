#pragma once
#include <cstdarg>
#include <ctime>
#include <direct.h>
#include <iostream>
#include <string>
#include <fstream>

#include "ILogger.h"

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
		string environment;
		fstream fileLog;
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

		void info(string message) override;
		void debug(string message) override;
		void warning(string message) override;
		void error(string message) override;
		void writeDebug(const char* templates, ...) override;
	private:
		string now() const;
		void writeStart(fstream& file) const;
		void close() noexcept;
	};
}
