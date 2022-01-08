#pragma once
#include <stdexcept>

#include "MachineStep.h"
#include <functional>

namespace Lex
{
	class Das
	{
		std::string firsStepId;
		std::map<std::string, MachineStep> steps;
		std::map<std::string, std::function<void(std::string)>> callbackFunctions;
	public:
		void addStep(const std::string& stepId, const MachineStep& machineStep);
		void addCallbackFunction(std::string token, std::function<void(std::string) >fun);

		bool hasStep(const std::string& stepId);

		void runCallbackForToken(std::string token, std::string value);

		MachineStep getStep(std::string stepId);

		std::string getFirstStepId()
		{
			return this->firsStepId;
		}

		MachineStep getFirstStep()
		{
			return this->getStep(this->getFirstStepId());
		}

		int getStepSize()
		{
			return steps.size();
		}
	};
}