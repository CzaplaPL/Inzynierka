#pragma once
#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/LekserException.h"
#include "PreviewElement.h"
#include "RegexConstructorSyntaxTree.h"

/// <summary>
/// klasa dostarcza funkcje do regexow
/// </summary>
class RegexService : private RegexConstructorSyntaxTree
{
	int nextid = 0;
	Logger* logger;
public:

	RegexService(Logger& logger) : RegexConstructorSyntaxTree(&logger)
	{
		this->logger = &logger;
	}

	/// <summary>
	/// klasa tworzy drzewo rozk≥adu z podanego regexa
	/// </summary>
	/// <param name="reg">regex</param>
	/// <returns>wskaünik na RegexNode wskazujacy na drzewo rozk≥adu</returns>
	RegexNode* generateTree(std::string& reg);

	/// <summary>
	/// funkcja konwertujaca RegexNodeType na stringa
	/// </summary>
	/// <param name="type"></param>
	/// <returns>string z nazwa typu</returns>
	static string regexNodeTypeToString(RegexNodeType type);
	/// <summary>
	/// funkcja sprawdza czy dany znak jest znakiem specjalnym
	/// </summary>
	/// <param name="value"></param>
	/// <returns>true gdy znak jest znakiem specjalnym</returns>
	bool isSpecialChar(char value);
};
