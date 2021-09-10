#include "RegexService.h"


RegexNode* RegexService::generateTree(std::string& reg)
{
	RegexNode* tree = nullptr;

	PreviewElement previewElement= PreviewElement(reg[0]);
	for (int i = 1; i < reg.length(); ++i)
	{
		try
		{
			switch (previewElement.type)
			{
			case RegexNodeType::OR:
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

void(RegexService::* RegexService::checkAction(char value))()
{
	return &myfun;
}

//action RegexService::checkAction(char value)
//{
//	 &myfun;
//	return &myfun();
//}
//
//
//void RegexService::myfun()
//{
//	this->logger->error("odp = ");
//}
//
//void RegexService::nofun()
//{
//	this->logger->error("odp = ");
//}
