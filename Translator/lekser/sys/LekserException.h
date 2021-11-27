#pragma once
#include <exception>
#include <string>

using namespace std;

class LekserException : public exception
{
	string message;
public:
	LekserException(string mesg)
	{
		this->message = mesg;
	}
	const char* what() const noexcept override  {
		return message.data();
	}
};
