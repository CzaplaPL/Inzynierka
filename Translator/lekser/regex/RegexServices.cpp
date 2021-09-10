#include "RegexServices.h"

RegexNode* RegexServices::generateTree(std::string& reg)
{
	RegexNode* tree = nullptr;

	for (int i = 1; i < reg.length(); ++i)
	{
		try
		{
			switch (reg[i])
			{
			case '|':
				break;
			default:

				break;
			}
		}
		catch (std::out_of_range& exception)
		{
			logger->error("b��d podczas tworzenia regexTree");
			if (i == reg.length() - 1)
				logger->error("b��dne zako�czenie regexa");
			logger->error(exception.what());
			logger->debug(reg);
		}
		catch (std::exception& exception)
		{
			logger->error("b��d podczas tworzeniae regexTree");
			logger->error("b�ad na znaku" + reg[i]);
			logger->error("nr :" + i);
			logger->error(exception.what());
			logger->debug(reg);
			throw RegexException("b��d podczas tworzenia drzewa rozk�adu regexa");
		}
	}

	return tree;
}