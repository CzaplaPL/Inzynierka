#pragma once
#include <map>
#include <string>
#include <vector>
#include "Uuid.h"

using namespace std;
/// <summary>
/// zwraca wygenerowany uuid
/// Je¿eli dla podanej struktury zosta³ ju¿ wygenerowany id to nie generuje nowego ale zwraca uuid przypisane do podanej struktury
/// </summary>
class IdCreator
{
	map<string, string> stepIds;
public:
	/// <summary>
	/// Czyœci zapisane informacje o wygenerowanych uuid
	/// </summary>
	/// <returns></returns>
	void clearMap();
	string generateId(const vector<int>& vector);
	string generateId(const vector<std::string>& vector);
};
