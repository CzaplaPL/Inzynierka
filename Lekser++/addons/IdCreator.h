#pragma once
#include <map>
#include <string>
#include <vector>
#include "Uuid.h"

namespace Lex
{
	/// <summary>
	/// zwraca wygenerowany uuid
	/// Je�eli dla podanej struktury zosta� ju� wygenerowany id to nie generuje nowego ale zwraca uuid przypisane do podanej struktury
	/// </summary>
	class IdCreator
	{
		std::map<std::string, std::string> stepIds;
	public:
		/// <summary>
		/// Czy�ci zapisane informacje o wygenerowanych uuid
		/// </summary>
		/// <returns></returns>
		void clearMap();
		std::string generateId(const std::vector<int>& vector);
		std::string generateId(const std::vector<std::string>& vector);
	};
}