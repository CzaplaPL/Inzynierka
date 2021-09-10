#pragma once
#include <exception>
#include <string>

using namespace std;

class RegexException : public exception
{
	string message;
public:
	RegexException(string mesg)
	{
		this->message = mesg;
	}
	const char* what() const throw () {
		return message.data();
	}
};
