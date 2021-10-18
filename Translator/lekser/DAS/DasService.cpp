#include "DasService.h"

Lekser DasServices::generateLekser(vector<pair<string, string>> elements)
{
	vector < Das > Dases;
	for (pair<string, string> element : elements)
	{
		int id = 0;
		RegexNode* tree = this->regexService.generateTree(element.second, id);
		Dases.emplace_back(this->dasBuilder.generateDas(tree, element.first));
	}

	return Lekser();
}