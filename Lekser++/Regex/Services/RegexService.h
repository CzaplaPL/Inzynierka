#pragma once
#include "../RegexNode.h"
#include "../../addons/ILogger.h"
#include "../../sys/exception/LekserException.h"
#include "../PreviewElement.h"
#include "RegexConstructorSyntaxTree.h"
namespace Lex
{
	/// <summary>
	/// klasa dostarcza funkcje do regexow
	/// </summary>
	class RegexService : private RegexConstructorSyntaxTree
	{
		std::shared_ptr<ILogger> logger;
	public:

		RegexService(std::shared_ptr<ILogger> logger) : RegexConstructorSyntaxTree(logger)
		{
			this->logger = logger;
		}

		/// <summary>
		/// klasa tworzy drzewo rozk≥adu z podanego regexa
		/// </summary>
		/// <param name="reg">regex</param>
		/// <returns>wskaünik na RegexNode wskazujacy na drzewo rozk≥adu</returns>
		Lex::RegexNode* generateTree(std::string& reg, int& id);

		/// <summary>
		/// funkcja konwertujaca RegexNodeType na stringa
		/// </summary>
		/// <param name="type"></param>
		/// <returns>string z nazwa typu</returns>
		static std::string regexNodeTypeToString(Lex::RegexNodeType type);
		/// <summary>
		/// funkcja sprawdza czy dany znak jest znakiem specjalnym
		/// </summary>
		/// <param name="value"></param>
		/// <returns>true gdy znak jest znakiem specjalnym</returns>
		bool isSpecialChar(char value);
	};
}