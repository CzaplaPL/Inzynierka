#include "RegexService.h"

void my_int_func(int x)
{
	printf("%d\n", x);
}

RegexNode* RegexService::generateTree(std::string& reg)
{
	shared_ptr<RegexNode> tree;

	shared_ptr<RegexNode>(RegexConstructorSyntaxTree:: * action)(char&, char&, shared_ptr<RegexNode>&) = NULL;

	if (reg[0] == '(')
	{
		//to do
	}

	PreviewElement previewElement = PreviewElement(reg[0]);
	tree->setType(previewElement.type);
	tree->setValue(reg[0]);
	for (int i = 1; i < reg.length(); ++i)
	{
		try
		{
			if (reg[i] == '(')
			{
				//to do
			}
			switch (previewElement.type)
			{
			case RegexNodeType::OR:

				break;
			default:
				if (reg[i] == '\\')i += 1;
				action = this->checkAction(reg[i]);
				break;
			}
			(*this.*action)(reg[i - 1], reg[i], tree);
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