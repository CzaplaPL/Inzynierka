#pragma once

#include <string>

#include "RegexNodeType.h"

namespace Lex
{
	class PreviewElement
	{
	public:
		std::string value;
		RegexNodeType type;

		PreviewElement(char element);
		void setElement(char element);
	};
}
