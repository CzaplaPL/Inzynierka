#include "RegexService.h"

void my_int_func(int x)
{
	printf("%d\n", x);
}

RegexNode* RegexService::generateTree(std::string& reg)
{
	this->logger->debug("budowanie drzewa rozk³adu");
	shared_ptr<RegexNode> tree(new RegexNode);

	RegexNode*(RegexConstructorSyntaxTree:: * action)(char&, char&, shared_ptr<RegexNode>&) = NULL;

	if (reg[0] == '(')
	{
		// todo
	}

	//todo [] operator
	PreviewElement previewElement = PreviewElement(reg[0]);
	this->logger->debug(previewElement.toString());
	tree->setType(previewElement.type);
	tree->setValue(reg[0]);

	for (int i = 1; i < reg.length(); ++i)
	{
		this->logger->debug("znak nr " + std::to_string(i));
		this->logger->info(tree->toString());
		try
		{
			if (reg[i] == '\\')i += 1;
			if (reg[i] == '(')
			{
				//todo
				continue;
			}
			switch (previewElement.type)
			{
			case RegexNodeType::OR:
				if (isSpecialChar(reg[i]))throw RegexException("znak specjalny po | jest niedozwolony");
				tree->setSecondChild(RegexNodeType::ID, reg[i]);
				logger->info("dodawanie second child to or");
				break;
			default:
				action = this->checkAction(reg[i]);

				break;
			}
			tree.reset( (*this.*action)(reg[i - 1], reg[i], tree));
			previewElement.setElement(reg[i]);
		}
		catch (std::out_of_range& exception)
		{
			logger->error("b³¹d podczas tworzenia regexTree");
			if (i == reg.length() - 1)
				logger->error("b³êdne zakoñczenie regexa");
			logger->error(exception.what());
			logger->debug(reg);
		}catch (RegexException exception)
		{
			logger->error("b³¹d podczas tworzeniae regexTree");
			logger->error("b³ad na znaku" + reg[i]);
			logger->error("nr :" + i);
			logger->error(exception.what());
			logger->debug(reg);
			throw RegexException("b³¹d podczas tworzenia drzewa rozk³adu regexa");
		}catch (std::exception& exception)
		{
			logger->error("b³¹d podczas tworzeniae regexTree");
			logger->error("b³ad na znaku" + reg[i]);
			logger->error("nr :" + i);
			logger->error(exception.what());
			logger->debug(reg);
			throw RegexException("b³¹d podczas tworzenia drzewa rozk³adu regexa");
		}
	}
	return tree.get();
}

string RegexService::regexNodeTypeToString(RegexNodeType type)
{
	switch (type)
	{
	case RegexNodeType::ID:
		return "ID";
		break;
	case RegexNodeType::BLOCK:
		return "BLOCK";
		break;
	case RegexNodeType::OR:
		return "OR";
		break;
	case RegexNodeType::STAR:
		return "STAR";
		break;
	case RegexNodeType::PLUS:
		return "PLUS";
		break;
	case RegexNodeType::QUESTION:
		return "QUESTION";
		break;
	default:
		return "nieznany";
	}
}

bool RegexService::isSpecialChar(char value)
{
	if (value == '|' || value == '*')return true;
	return false;
}
