#pragma once
#include <string>

namespace Lex
{
	class StepInDas
	{
		int dasId;
		std::string stepId;
	public:

		StepInDas(int dasId, std::string stepId);
		int getDasId();
		std::string getId();
	};
}
