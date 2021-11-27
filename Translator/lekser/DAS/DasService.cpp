#include "DasService.h"
#include "NasStep.h"
#include "StepInDas.h"

Lekser DasService::generateLekser(vector<pair<string, string>> elements)
{
	vector < Das > Dases;
	for (pair<string, string> element : elements)
	{
		int id = 0;
		RegexNode* tree = this->regexService.generateTree(element.second, id);
		Dases.emplace_back(this->dasBuilder.generateDas(tree, element.first));
	}
	Das lekserMachine = mergeDases(Dases);
	return Lekser();
}

Das DasService::mergeDases(vector<Das>& dases)
{
	this->idCreator.clearMap();
	vector<StepInDas> firstSteps;
	queue<NasStep> indefiniteSteps;
	Das dasToReturn("");
	vector<string> firstStepsId;

	for (int i = 0; i < dases.size(); ++i)
	{
		firstStepsId.push_back(dases[i].getFirstStepId());
		firstSteps.emplace_back(i, dases[i].getFirstStepId());
	}
	string firstStepId = this->idCreator.generateId(firstStepsId);
	indefiniteSteps.push(NasStep(firstSteps, firstStepId));

	while (indefiniteSteps.size() > 0)
	{
		NasStep indefiniteStep = indefiniteSteps.front();
		indefiniteSteps.pop();
		map<string, vector<StepInDas> > newTransitions;

		string acceptingToken = "";
		for (StepInDas step : indefiniteStep.getSteps())
		{
			MachineStep dasStep = dases[step.getDasId()].getStep(step.getId());
			map<string, string> followPosition = dasStep.getTransitionsMap();

			for (map<string, string>::iterator transition = followPosition.begin(); transition != followPosition.end(); ++transition)
			{
				newTransitions[transition->first].push_back(StepInDas(step.getDasId(), transition->second));
			}
			if (dasStep.stepIsAccepting()) acceptingToken = dases[step.getDasId()].getToken();
		}
		map <string, string> transitionWithId;
		for (pair<string, vector<StepInDas>> transition : newTransitions)
		{
			vector<StepInDas> transitionSteps(transition.second.begin(), transition.second.end());
			vector<string> transitionStepsId;
			for (auto transitionStep : transitionSteps)
			{
				transitionStepsId.push_back(transitionStep.getId());
			}
			string transitionStepId = this->idCreator.generateId(transitionStepsId);
			if (!dasToReturn.hasStep(transitionStepId))
			{
				indefiniteSteps.push(NasStep(transitionSteps, transitionStepId));
			}
			transitionWithId.insert_or_assign(transition.first, transitionStepId);
		}
		if (acceptingToken.length() > 0)
		{
			dasToReturn.addStep(indefiniteStep.getStepId(), MachineStep(transitionWithId, true, acceptingToken));
		}
		else
		{
			dasToReturn.addStep(indefiniteStep.getStepId(), MachineStep(transitionWithId, false));
		}
	}

	return dasToReturn;
}