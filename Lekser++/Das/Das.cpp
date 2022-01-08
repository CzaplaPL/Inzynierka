#include "Das.h"

void Lex::Das::addStep(const std::string& stepId, const MachineStep& machineStep)
{
	if (this->steps.size() == 0)
	{
		firsStepId = stepId;
	}
	this->steps.insert_or_assign(stepId, machineStep);
}

void Lex::Das::addCallbackFunction(std::string token, std::function<void(std::string)> foo)
{
	std::map<std::string, std::function<void(std::string)>>::iterator it = this->callbackFunctions.find(token);
	if (it != this->callbackFunctions.end())
	{
		it->second = foo;
		return;
	}
	this->callbackFunctions.insert(std::pair<std::string, std::function<void(std::string)>>(token, foo));
}

bool Lex::Das::hasStep(const std::string& stepId)
{
	return this->steps.find(stepId) != this->steps.end();
}

void Lex::Das::runCallbackForToken(std::string token, std::string value)
{
	if (this->callbackFunctions.find(token) != this->callbackFunctions.end())
	{
		this->callbackFunctions[token](value);
	}
}

Lex::MachineStep Lex::Das::getStep(std::string stepId)
{
	if (!hasStep(stepId))throw std::out_of_range("brak wskazanego kroku ");
	return this->steps[stepId];
}