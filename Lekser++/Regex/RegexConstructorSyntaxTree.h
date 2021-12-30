#pragma once
#include <iostream>

#include "RegexNode.h"
#include "../addons/Logger.h"
#include "../sys/exception/LekserException.h"
#include "PreviewElement.h"
#include <memory>
#include <functional>

using namespace std;

namespace Lex
{
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
		//Lex::RegexNode* (RegexConstructorSyntaxTree::* checkAction(char& symbol))(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);

		Lex::RegexNode* (*checkAction(char& symbol))(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);

		/// <summary>
		/// funkcja dodaj�ca znak | do drzewa rozkladu
		/// </summary>
		/// <param name="firstChar"></param>
		/// <param name="secondChar"></param>
		/// <param name="tree"></param>
		/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addOr(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);
		/// <summary>
		/// funkcja dodajca znak � do drzewa rozk�adu
		/// </summary>
		/// <param name="previewElement"></param>
		/// <param name="curentElement"></param>
		/// <param name="tree"></param>
		/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addCombine(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);
		/// <summary>
		/// funkcja dodajca znak * do drzewa rozk�adu
		/// </summary>
		/// <param name="previewElement"></param>
		/// <param name="curentElement"></param>
		/// <param name="tree"></param>
		/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addStar(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);
		/// <summary>
		/// funkcja dodajca znak + do drzewa rozk�adu
		/// </summary>
		/// <param name="previewElement"></param>
		/// <param name="curentElement"></param>
		/// <param name="tree"></param>
		/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addPlus(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);
		/// <summary>
		/// funkcja dodajca znak ? do drzewa rozk�adu
		/// </summary>
		/// <param name="previewElement"></param>
		/// <param name="curentElement"></param>
		/// <param name="tree"></param>
		/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addQuestion(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);
		/// <summary>
		/// funkcja dodajca drzewo rozka�du z ()
		/// </summary>
		/// <param name="previewElement"></param>
		/// <param name="curentElement"></param>
		/// <param name="tree"></param>
		/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addBrackets(PreviewElement previewElement, RegexNode* tree, RegexNode* treeInBrackets, int& id);
		/// <summary>
	/// funkcja obs�uguj�ca {} w drzewie rozk�adu
	/// </summary>
	/// <param name="previewElement"></param>
	/// <param name="curentElement"></param>
	/// <param name="tree"></param>
	/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addMustageBrackets(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);
		/// funkcja obs�uguj�ca [] w drzewie rozk�adu
		/// </summary>
		/// <param name="previewElement"></param>
		/// <param name="curentElement"></param>
		/// <param name="tree"></param>
		/// <returns>nowe drzewo rozk�adu</returns>
		static Lex::RegexNode* addBlock(PreviewElement previewElement, string& regex, RegexNode* tree, int& id);

		void print_num(int i)
		{
			std::cout << i << '\n';
		}

	private:
		static int countCharLenght(string& regex);
	};
}