#pragma once
namespace Lex
{
	enum class RegexNodeType
	{
		ID,
		BLOCK,
		OR,
		STAR,
		PLUS,
		QUESTION,
		COMBINE,
		END,
	};
}