#include "MachineStep.h"

Lex::MachineStep::MachineStep(std::map<std::string, std::string>& transitions, bool isAccepting, std::string id, std::string token) :transitionsMap(transitions)
{
	this->id = id;
	this->isAccepting = isAccepting;
	this->token = token;
}

Lex::MachineStep::MachineStep()
{
	this->isAccepting = false;
}

std::string Lex::MachineStep::getStepIdForString(std::string key)
{
	if (this->transitionsMap.find(key) == this->transitionsMap.end())
	{
		for (auto element : this->transitionsMap)
		{
			if (element.first[1] == '-' && element.first.size() == 3)
			{
				if (*key.c_str() >= element.first[0] && *key.c_str() <= element.first[2])
				{
					return element.second;
				}
			}
		}
		throw NoStepException("brak wskazanego kroku dla " + key);
	}
	return this->transitionsMap[key];
}