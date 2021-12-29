#pragma once
#include <stdexcept>

#include "MachineStep.h"

namespace Lex
{
	class Das
	{
		std::string firsStepId;
		std::map<std::string, MachineStep> steps;
	public:
		void addStep(const std::string& stepId, const MachineStep& machineStep);

		bool hasStep(const std::string& stepId);

		MachineStep getStep(std::string stepId);

		std::string getFirstStepId()
		{
			return this->firsStepId;
		}

		int getStepSize()
		{
			return steps.size();
		}
	};
}