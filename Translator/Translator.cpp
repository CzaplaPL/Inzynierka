#include <iostream>

#include "Lekser++.h"

#define DEBUG true
#define ENV "dev"

string readToken(std::string::iterator it, std::string::iterator end)
{
	try {
		for (; it != end; ++it)
		{
			std::cout << *it << " ";
		}
	}
	catch (std::exception& exception)
	{
		cout << exception.what();
	}

	return "bbb";
}

int main()
{
	Lekser lex("tekst.txt");

	cin.get();
}