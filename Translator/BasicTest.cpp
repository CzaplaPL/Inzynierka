#include "BasicTest.h"
#include <iostream>

int BasicTest::getCount()
{
	std::cout << "witaj w tescie";
	return count * 2;
}

inline void BasicTest::setCount(int count)
{
	this->count = count;
}