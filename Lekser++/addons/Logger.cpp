#include "Logger.h"

namespace Lex
{
	string const Logger::VERSION = "0.0.5";

	Logger::Logger(string environment)
	{
		this->isDebug = false;
		this->isTime = true;
		this->environment = environment;
		_mkdir("log");

		string environmentDir = "log/" + environment;
		_mkdir(environmentDir.c_str());

		fileLog.open("log/" + environment + "/log.log", ios::trunc | ios::in | ios::out);

		writeStart(fileLog);

		this->isTime = false;
	}

	Logger::~Logger()
	{
		close();
	}

	void Logger::setDebug(const bool isDebug) noexcept
	{
		this->isDebug = isDebug;
	}

	void Logger::setTime(const bool isTime) noexcept
	{
		this->isTime = isTime;
	}

	void Logger::info(const string message)
	{
		fileLog << now() << message << endl;
	}

	void Logger::debug(const string message)
	{
		fileLog << "[DEBUG] " << now() << " " << message << endl;
		if (isDebug)
		{
			std::cout << "[DEBUG] " << now() << " " << message << endl;
		}
	}

	void Logger::warning(const string message)
	{
		fileLog << "[WARNING] " << now() << " " << message << endl;
	}

	void Logger::error(const string message)
	{
		fileLog << "[ERROR] " << now() << " " << message << endl;
		std::cout << "\033[1;31m " << "[ERROR] " << now() << " " << message << "\033[0m\n" << endl;
	}

	void Logger::writeDebug(const char* templates, ...)
	{
		if (isDebug)
		{
			fileLog << "[DEBUG] " << now() << " ";

			va_list vl = nullptr;
			va_start(vl, templates);

			union option_t {
				int     i = 0;
				double   d;
				char    c;
				char* s;
			} option;

			for (int i = 0; templates[i] != '\0'; ++i)
			{
				switch (templates[i]) {   // Type to expect.
				case 'i':
					option.i = va_arg(vl, int);
					fileLog << option.i;
					break;
				case 'd':
					option.d = va_arg(vl, double);
					fileLog << option.d;
					break;
				case 'c':
					option.c = va_arg(vl, char);
					fileLog << option.c;
					break;
				case 's':
					option.s = va_arg(vl, char*);
					fileLog << option.s;
					break;
				default:
					break;
				}
			}
			fileLog << endl;
			__crt_va_end(vl);
		}
	}

	string Logger::now() const
	{
		if (isTime)
		{
			time_t rawtime;
			struct tm timeinfo;
			char buffer[80];

			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);

			strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
			string str(buffer);

			return str;
		}
		return "";
	}

	void Logger::writeStart(fstream& file) const
	{
		file << "log Translator " << VERSION << endl;
		file << "autor: Czapla " << endl;
		file << "data uruchomienia : " << now() << endl;
	}

	void Logger::close() noexcept
	{
		try
		{
			fileLog.close();
		}
		catch (exception e)
		{
		}
	}
}