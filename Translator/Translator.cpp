#include <iostream>

#include "addons/Logger.h"
#include "lekser/DAS/Das.h"
#include "lekser/DAS/DasServices.h"
#include "lekser/regex/RegexNode.h"
#include "lekser/regex/RegexService.h"
#define DEBUG true
#define ENV "dev"

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);
	string reg = "(a*|b*)*#";
	RegexService* regexService = new RegexService(log);
	DasServices* dasServices = new DasServices(log);
	int id = 0;
	RegexNode* tree = regexService->generateTree(reg, id);
	Das as = dasServices->generateDas(tree);
	cin.get();
}