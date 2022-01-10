#pragma once

#include <string>
#include <vector>

#include "MachineStep.h"
#include "StepInDas.h"

namespace Lex
{
	class NasStep
	{
		std::string stepId;
		std::vector<StepInDas> dasSteps;
		std::map<std::string, StepInDas> transitions;
		bool isAccepting;
		std::string token;
	public:
		NasStep(std::vector<StepInDas> dasSteps, std::string stepId);

		std::vector<StepInDas> getSteps()
		{
			return this->dasSteps;
		}

		void setAccepting(const std::string& token);

		std::string getStepId()
		{
			return this->stepId;
		}
	};
}
