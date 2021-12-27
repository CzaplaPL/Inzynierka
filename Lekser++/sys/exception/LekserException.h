#pragma once
#include <exception>
#include <string>

class LekserException : public std::exception
{
	std::string message;
public:
	LekserException(std::string mesg)
	{
		this->message = mesg;
	}
	const char* what() const noexcept override {
		return message.data();
	}
};
