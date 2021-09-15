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
	RegexNode* (RegexConstructorSyntaxTree::* checkAction(char& symbol))(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodaj�ca znak | do drzewa rozkladu
	/// </summary>
	/// <param name="firstChar"></param>
	/// <param name="secondChar"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
	RegexNode* addOr(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak � do drzewa rozk�adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
	RegexNode* addCombine(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak * do drzewa rozk�adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
	RegexNode* addStar(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak + do drzewa rozk�adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
	RegexNode* addPlus(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak ? do drzewa rozk�adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
	RegexNode* addQuestion(PreviewElement previewElement, string& regex, RegexNode* tree);

	/// <summary>
	/// funkcja dodajca drzewo rozka�du z ()
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
	RegexNode* addBrackets(PreviewElement previewElement, string& regex, RegexNode* tree);
};
