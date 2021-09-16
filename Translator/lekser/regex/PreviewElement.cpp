#include "PreviewElement.h"

#include "RegexService.h"

PreviewElement::PreviewElement(char element)
{
	this->setElement(element);
}

void PreviewElement::setElement(char element)
{
	this->value = element;
	switch (element)
	{
	case'|':
		this->type = RegexNodeType::OR;
		break;
	case'[':
		this->type = RegexNodeType::BLOCK;
		break;
	case'*':
		this->type = RegexNodeType::STAR;
		break;
	case'?':
		this->type = RegexNodeType::QUESTION;
		break;
	case'+':
		this->type = RegexNodeType::PLUS;
		break;
	default:
		this->type = RegexNodeType::ID;
		break;
	}
}

std::string PreviewElement::toString()
{
	std::string toReturn = "previewElement : value = " + value + " type = ";
	toReturn += RegexService::regexNodeTypeToString(type);
	return toReturn;
}