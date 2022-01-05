#include "Logger.h"

namespace Lex
{
	std::string const Logger::VERSION = "0.0.5";

	Logger::Logger(std::string environment)
	{
		this->isDebug = false;
		this->isTime = true;
		this->environment = environment;
		_mkdir("log");

		std::string environmentDir = "log/" + environment;
		_mkdir(environmentDir.c_str());

		fileLog.open("log/" + environment + "/log.log", std::ios::trunc | std::ios::in | std::ios::out);

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

	void Logger::info(const std::string message)
	{
		fileLog << now() << message << std::endl;
	}

	void Logger::debug(const std::string message)
	{
		fileLog << "[DEBUG] " << now() << " " << message << std::endl;
		if (isDebug)
		{
			std::cout << "[DEBUG] " << now() << " " << message << std::endl;
		}
	}

	void Logger::warning(const std::string message)
	{
		fileLog << "[WARNING] " << now() << " " << message << std::endl;
	}

	void Logger::error(const std::string message)
	{
		fileLog << "[ERROR] " << now() << " " << message << std::endl;
		std::cout << "\033[1;31m " << "[ERROR] " << now() << " " << message << "\033[0m\n" << std::endl;
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
			fileLog << std::endl;
			__crt_va_end(vl);
		}
	}

	std::string Logger::now() const
	{
		if (isTime)
		{
			time_t rawtime;
			struct tm timeinfo;
			char buffer[80];

			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);

			strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
			std::string str(buffer);

			return str;
		}
		return "";
	}

	void Logger::writeStart(std::fstream& file) const
	{
		file << "log Translator " << VERSION << std::endl;
		file << "autor: Czapla " << std::endl;
		file << "data uruchomienia : " << now() << std::endl;
	}

	void Logger::close() noexcept
	{
		try
		{
			fileLog.close();
		}
		catch (std::exception e)
		{
		}
	}
}