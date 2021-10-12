#include <iostream>

#include "addons/Logger.h"
#include "lekser/DAS/Das.h"
#include "lekser/DAS/DasService.h"
#include "lekser/regex/RegexNode.h"
#include "lekser/regex/RegexService.h"
#define DEBUG true
#define ENV "dev"

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);
	string reg = "(a|b)*abb";
	RegexService* regexService = new RegexService(log);
	DasService* dasServices = new DasService(log);
	int id = 0;
	RegexNode* tree = regexService->generateTree(reg, id);
	Das as = dasServices->generateDas(tree);
	cin.get();
}