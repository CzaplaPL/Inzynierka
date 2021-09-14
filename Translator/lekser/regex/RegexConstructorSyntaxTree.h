#pragma once
#include <iostream>

#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/RegexException.h"
#include "PreviewElement.h"
#include <memory>

using namespace std;
/// <summary>
/// klasa zawierajaca funkcje do tworzenia drzewa rozk�adu
/// </summary>
class RegexConstructorSyntaxTree
{
	Logger* logger;
public:

	RegexConstructorSyntaxTree(Logger* logger)
	{
		this->logger = logger;
	}

protected:
	/// <summary>
	/// funkcja zwraca wskaznik na funkcje kt�r� trzeba wykona�
	/// </summary>
	/// <param name="symbol">znak dla kt�rego chcemy sprawdzi� jak� funkcje wykona�</param>
	/// <returns>wska�nik do odpowiedniej funkcji</returns>
	RegexNode*(RegexConstructorSyntaxTree::* checkAction(char &symbol))(char& firstChar, char& secondChar, RegexNode* tree);
	/// <summary>
	/// funkcja dodaj�ca znak | do drzewa rozkladu
	/// </summary>
	/// <param name="firstChar"></param>
	/// <param name="secondChar"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
	RegexNode* addOr(char& firstChar, char& secondChar, RegexNode* tree);
};
