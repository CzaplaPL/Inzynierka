#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>

#include "../sys/exception/NoStepException.h"

namespace Lex
{
	class MachineStep
	{
		bool isAccepting;
		std::string token;
		std::map<std::string, std::string> transitionsMap;
		std::string id;
	public:
		MachineStep(std::map<std::string, std::string>& transitions, bool isAccepting, std::string id, std::string token = "");
		MachineStep();

		std::string getStepIdForString(std::string key);

		std::map<std::string, std::string> getTransitionsMap()
		{
			return this->transitionsMap;
		}
		std::string getAcceptingToken()
		{
			return this->token;
		}

		std::string getId()
		{
			return this->id;
		}

		bool stepIsAccepting()
		{
			return this->isAccepting;
		}
	};
}