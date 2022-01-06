#pragma once
#include <string>
namespace Lex
{
	class Definition
	{
		std::string regex;
		std::string token;
	public:
		Definition(std::string regex, std::string token)
		{
			this->regex = regex;
			this->token = token;
		}

		std::string getRegex()
		{
			return regex;
		}

		std::string getToken()
		{
			return token;
		}
	};
}