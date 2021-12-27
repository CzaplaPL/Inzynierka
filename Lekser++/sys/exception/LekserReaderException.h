#pragma once
#include <exception>
#include <string>

using namespace std;

class LekserReaderException : public exception
{
	string message;
public:
	LekserReaderException(string mesg)
	{
		this->message = mesg;
	}
	const char* what() const noexcept override {
		return message.data();
	}
};
