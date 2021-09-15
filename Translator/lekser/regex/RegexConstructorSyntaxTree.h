#pragma once
#include <iostream>

#include "../Translator/lekser/regex/RegexNode.h"
#include "../Translator/addons/Logger.h"
#include "../Translator/addons/RegexException.h"
#include "PreviewElement.h"
#include <memory>

using namespace std;
/// <summary>
/// klasa zawierajaca funkcje do tworzenia drzewa rozk³adu
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
	/// funkcja zwraca wskaznik na funkcje któr¹ trzeba wykonaæ
	/// </summary>
	/// <param name="symbol">znak dla którego chcemy sprawdziæ jak¹ funkcje wykonaæ</param>
	/// <returns>wska¿nik do odpowiedniej funkcji</returns>
	RegexNode* (RegexConstructorSyntaxTree::* checkAction(char& symbol))(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodaj¹ca znak | do drzewa rozkladu
	/// </summary>
	/// <param name="firstChar"></param>
	/// <param name="secondChar"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk³adu</returns>
	RegexNode* addOr(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak ° do drzewa rozk³adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk³adu</returns>
	RegexNode* addCombine(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak * do drzewa rozk³adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk³adu</returns>
	RegexNode* addStar(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak + do drzewa rozk³adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk³adu</returns>
	RegexNode* addPlus(PreviewElement previewElement, string& regex, RegexNode* tree);
	/// <summary>
	/// funkcja dodajca znak ? do drzewa rozk³adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk³adu</returns>
	RegexNode* addQuestion(PreviewElement previewElement, string& regex, RegexNode* tree);

	/// <summary>
	/// funkcja dodajca drzewo rozka³du z ()
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk³adu</returns>
	RegexNode* addBrackets(PreviewElement previewElement, string& regex, RegexNode* tree);
};
