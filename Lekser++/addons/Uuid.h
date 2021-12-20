#pragma once
#include <string>
#include <cstdlib>

class Uuid
{
public:
	/// <summary>
	/// generuje uuid xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
	/// </summary>
	/// <returns>std::string uuid</returns>
	static std::string generateUUID();
};
