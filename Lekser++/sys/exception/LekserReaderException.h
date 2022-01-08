#pragma once

#include <exception>
#include <string>

class LekserReaderException : public std::exception
{
	std::string message;
public:
	LekserReaderException(std::string mesg)
	{
		this->message = mesg;
	}
	const char* what() const noexcept override {
		return message.data();
	}
};
