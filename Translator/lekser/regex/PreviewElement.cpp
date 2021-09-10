#include "PreviewElement.h"

PreviewElement::PreviewElement(char element)
{
	this->value = element;
	switch (element)
	{
	case'|':
		this->type = RegexNodeType::OR;
		break;
	default:
		this->type = RegexNodeType::ID;
		break;
	}
}
