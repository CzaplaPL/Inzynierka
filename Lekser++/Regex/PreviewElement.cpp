#include "PreviewElement.h"

Lex::PreviewElement::PreviewElement(char element)
{
	this->setElement(element);
}

void Lex::PreviewElement::setElement(char element)
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
	case']':
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