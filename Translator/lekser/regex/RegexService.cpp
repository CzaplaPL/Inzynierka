#include "RegexService.h"

RegexNode* RegexService::generateTree(std::string& reg)
{
	this->logger->debug("budowanie drzewa rozk³adu");

	RegexNode* tree = new RegexNode;
	RegexNode* (RegexConstructorSyntaxTree:: * action)(PreviewElement previewElement, string & regex, RegexNode*) = NULL;
	PreviewElement previewElement = PreviewElement(reg[0]);
	if (reg[0] == '(')
	{
		this->logger->debug("zaczynam od nawiasu");
		reg.erase(0, 1);
		tree = this->generateTree(reg);
	}
	else
	{
		//todo [] operator
		tree->setType(previewElement.type);
		tree->setValue(reg[0]);
		reg.erase(0, 1);
	}
	this->logger->debug(previewElement.toString());
	while (reg.length())
	{
		this->logger->debug("nastêpny znak");
		this->logger->info(tree->toString());
		try
		{
			if (reg[0] == ')')
			{
				return tree;
			}
			switch (previewElement.type)
			{
			case RegexNodeType::OR:
				if (isSpecialChar(reg[0]))throw RegexException("znak specjalny po | jest niedozwolony");
				if (reg[0] == '\\')reg.erase(0, 1);
				tree->setSecondChild(RegexNodeType::ID, reg[0]);
				logger->info("dodawanie second child to or");
				break;
			default:
				action = this->checkAction(reg[0]);

				if (reg[0] == '\\')reg.erase(0, 1);
				tree = (*this.*action)(previewElement, reg, tree);

				break;
			}

			previewElement.setElement(reg[0]);
			reg.erase(0, 1);
		}
		catch (std::out_of_range& exception)
		{
			logger->error("b³¹d podczas tworzenia regexTree");

			logger->error(exception.what());
			logger->debug(reg);
		}
		catch (RegexException exception)
		{
			logger->error("b³¹d podczas tworzeniae regexTree");
			logger->error("b³ad na znaku" + reg[0]);
			logger->error(exception.what());
			logger->debug(reg);
			throw RegexException("b³¹d podczas tworzenia drzewa rozk³adu regexa");
		}
		catch (std::exception& exception)
		{
			logger->error("b³¹d podczas tworzeniae regexTree");
			logger->error("b³ad na znaku" + reg[0]);
			logger->error(exception.what());
			logger->debug(reg);
			throw RegexException("b³¹d podczas tworzenia drzewa rozk³adu regexa");
		}
	}
	logger->debug("koniec generowania drzewa");
	logger->info(tree->toString());

	return tree;
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
	case RegexNodeType::COMBINE:
		return "COMBINE";
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