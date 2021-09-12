#include "RegexService.h"

void my_int_func(int x)
{
	printf("%d\n", x);
}

RegexNode* RegexService::generateTree(std::string& reg)
{
	RegexNode* tree = nullptr;

	int (RegexConstructorSyntaxTree:: * pt2ConstMember)(float, char, char) = NULL;

	pt2ConstMember = this->checkAction();

	(*this.*pt2ConstMember)(12, 'a', 'b');

	PreviewElement previewElement = PreviewElement(reg[0]);
	for (int i = 1; i < reg.length(); ++i)
	{
		try
		{
			switch (previewElement.type)
			{
			case RegexNodeType::OR:
				break;
			default:
				//auto action = this->checkAction(reg[i]);
				//action();
				break;
			}
		}
		catch (std::out_of_range& exception)
		{
			logger->error("b³¹d podczas tworzenia regexTree");
			if (i == reg.length() - 1)
				logger->error("b³êdne zakoñczenie regexa");
			logger->error(exception.what());
			logger->debug(reg);
		}
		catch (std::exception& exception)
		{
			logger->error("b³¹d podczas tworzeniae regexTree");
			logger->error("b³ad na znaku" + reg[i]);
			logger->error("nr :" + i);
			logger->error(exception.what());
			logger->debug(reg);
			throw RegexException("b³¹d podczas tworzenia drzewa rozk³adu regexa");
		}
	}

	return tree;
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