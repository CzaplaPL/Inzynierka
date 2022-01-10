#pragma once

#include <exception>
#include <string>

class NoStepException : public std::exception
{
	std::string message;
public:
	NoStepException(std::string mesg)
	{
		this->message = mesg;
	}
	const char* what() const noexcept override {
		return message.data();
	}
};