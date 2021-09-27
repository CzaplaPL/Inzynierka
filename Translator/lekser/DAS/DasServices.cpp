#include "DasServices.h"

void DasServices::firstPos(RegexNode* tree)
{
	if(tree == nullptr) throw LekserException("nie istnieje firstpos dla pustego drzewa");
	if(tree->getType() == RegexNodeType::ID)
	{
		
	}
}
