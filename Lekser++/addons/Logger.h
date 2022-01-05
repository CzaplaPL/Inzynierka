#pragma once
#include <cstdarg>
#include <ctime>
#include <direct.h>
#include <iostream>
#include <fstream>

#include "ILogger.h"

namespace Lex
{
	/// <summary>
	/// Klasa odpowiedzialna za zapisywanie danych do logów
	/// </summary>
	class  __declspec(dllexport) Logger : public ILogger
	{
		bool isDebug;
		bool isTime;
		std::string environment;
		std::fstream fileLog;
	public:
		static const std::string VERSION;

		/// <param name="environment">srodowisko w jakim jest wykonywany program</param>
		Logger(std::string environment);

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

		void info(std::string message) override;
		void debug(std::string message) override;
		void warning(std::string message) override;
		void error(std::string message) override;
		void writeDebug(const char* templates, ...) override;
	private:
		std::string now() const;
		void writeStart(std::fstream& file) const;
		void close() noexcept;
	};
}
