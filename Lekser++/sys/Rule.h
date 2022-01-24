#pragma once

#include <string>
namespace Lex
{
	class Rule
	{
		std::string regex;
		std::string token;
	public:
		Rule(std::string regex, std::string token)
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