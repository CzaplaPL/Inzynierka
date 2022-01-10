#include "DasService.h"

Lex::Das Lex::DasService::generateLekser(std::vector<Lex::Definition> elements)
{
	std::vector < Das > Dases;
	for (Definition element : elements)
	{
		std::string regex = element.getRegex();
		int id = 0;
		RegexNode* tree = this->regexService.generateTree(regex, id);
		Dases.emplace_back(this->dasBuilder.generateDas(tree, element.getToken()));
		delete tree;
	}
	return mergeDases(Dases);
}

Lex::Das  Lex::DasService::mergeDases(std::vector<Das>& dases)
{
	this->idCreator.clearMap();
	std::vector<StepInDas> firstSteps;
	std::queue<NasStep> indefiniteSteps;
	Das dasToReturn;
	std::vector< std::string> firstStepsId;

	for (int i = 0; i < dases.size(); ++i)
	{
		firstStepsId.push_back(dases[i].getFirstStepId());
		firstSteps.emplace_back(i, dases[i].getFirstStepId());
	}
	std::string firstStepId = this->idCreator.generateId(firstStepsId);
	indefiniteSteps.push(NasStep(firstSteps, firstStepId));

	while (indefiniteSteps.size() > 0)
	{
		NasStep indefiniteStep = indefiniteSteps.front();
		indefiniteSteps.pop();
		std::map< std::string, std::vector<StepInDas> > newTransitions;

		std::string acceptingToken = "";
		for (StepInDas step : indefiniteStep.getSteps())
		{
			MachineStep dasStep = dases[step.getDasId()].getStep(step.getId());
			std::map< std::string, std::string> followPosition = dasStep.getTransitionsMap();

			for (std::map< std::string, std::string>::iterator transition = followPosition.begin(); transition != followPosition.end(); ++transition)
			{
				newTransitions[transition->first].push_back(StepInDas(step.getDasId(), transition->second));
			}
			if (dasStep.stepIsAccepting()) acceptingToken = dasStep.getAcceptingToken();
		}
		std::map < std::string, std::string> transitionWithId;
		for (std::pair< std::string, std::vector<StepInDas>> transition : newTransitions)
		{
			std::vector<StepInDas> transitionSteps(transition.second.begin(), transition.second.end());
			std::vector< std::string> transitionStepsId;
			for (auto transitionStep : transitionSteps)
			{
				transitionStepsId.push_back(transitionStep.getId());
			}
			std::string transitionStepId = this->idCreator.generateId(transitionStepsId);
			if (!dasToReturn.hasStep(transitionStepId))
			{
				indefiniteSteps.push(NasStep(transitionSteps, transitionStepId));
			}
			transitionWithId.insert_or_assign(transition.first, transitionStepId);
		}
		if (acceptingToken.length() > 0)
		{
			dasToReturn.addStep(indefiniteStep.getStepId(), MachineStep(transitionWithId, true, indefiniteStep.getStepId(), acceptingToken));
		}
		else
		{
			dasToReturn.addStep(indefiniteStep.getStepId(), MachineStep(transitionWithId, false, indefiniteStep.getStepId(), acceptingToken));
		}
	}

	return dasToReturn;
}