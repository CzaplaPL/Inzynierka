#pragma once
#include <exception>
#include <string>

using namespace std;

class NoStepException : public exception
{
	string message;
public:
	NoStepException(string mesg)
	{
		this->message = mesg;
	}
	const char* what() const noexcept override {
		return message.data();
	}
};