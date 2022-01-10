#include "RegexConstructorSyntaxTree.h"

Lex::RegexNode* (*Lex::RegexConstructorSyntaxTree::checkAction(char& symbol))(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	switch (symbol)
	{
	case '|':
		logger->info("return or function");
		return RegexConstructorSyntaxTree::addOr;
	case '*':
		logger->info("return star function");
		return RegexConstructorSyntaxTree::addStar;
	case '?':
		logger->info("return star function");
		return RegexConstructorSyntaxTree::addQuestion;
	case '+':
		logger->info("return plus function");
		return RegexConstructorSyntaxTree::addPlus;
	case '{':
		logger->info("return mustage brackets function");
		return RegexConstructorSyntaxTree::addMustageBrackets;
	case '[':
		logger->info("return block function");
		return RegexConstructorSyntaxTree::addBlock;
	default:
		logger->info("return combine function");
		return RegexConstructorSyntaxTree::addCombine;
	}
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addOr(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new  RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::OR);
	newTree->setId(id);
	id += 1;
	return newTree;
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addCombine(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree = new  RegexNode();
	newTree->setType(RegexNodeType::COMBINE);
	newTree->setId(id);
	newTree->setFirstChild(tree);
	id += 1;
	newTree->setSecondChild(RegexNodeType::ID, regex[0], id);
	id += 1;
	return newTree;
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addStar(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree;
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr)
	{
		newTree = new  RegexNode();
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::STAR);
		newTree->setId(id);
		id += 1;
		return newTree;
	}

	newTree = new  RegexNode(tree, nullptr);
	RegexNode* newSecondChild(new  RegexNode());
	newSecondChild->setType(RegexNodeType::STAR);
	newSecondChild->setFirstChild(secondChild);
	newSecondChild->setId(id);
	id += 1;
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addPlus(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new  RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::PLUS);
		newTree->setId(id);
		id += 1;
		return newTree;
	}
	newTree = new  RegexNode(tree, nullptr);
	RegexNode* newSecondChild(new  RegexNode());
	newSecondChild->setType(RegexNodeType::PLUS);
	newSecondChild->setFirstChild(secondChild);
	newSecondChild->setId(id);
	id += 1;
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addQuestion(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	RegexNode* newTree(new  RegexNode());
	RegexNode* secondChild = tree->getSecondChild();
	if (secondChild == nullptr)
	{
		newTree->setFirstChild(tree);
		newTree->setType(RegexNodeType::QUESTION);
		newTree->setId(id);
		id += 1;
		return newTree;
	}
	newTree = new  RegexNode(tree, nullptr);
	RegexNode* newSecondChild(new  RegexNode());
	newSecondChild->setType(RegexNodeType::QUESTION);
	newSecondChild->setFirstChild(secondChild);
	newSecondChild->setId(id);
	id += 1;
	newTree->setSecondChild(newSecondChild);
	return newTree;
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addBrackets(PreviewElement previewElement, RegexNode* tree, RegexNode* treeInBrackets, int& id)
{
	if (previewElement.type == RegexNodeType::OR)
	{
		tree->setSecondChild(treeInBrackets);
		return new  RegexNode(tree, nullptr);
	}

	RegexNode* newTree(new  RegexNode());
	newTree->setFirstChild(tree);
	newTree->setType(RegexNodeType::COMBINE);
	newTree->setId(id);
	id += 1;
	newTree->setSecondChild(treeInBrackets);
	return newTree;
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addMustageBrackets(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	std::string element = previewElement.value;
	if (regex[1] == ',')
	{
		regex.erase(0, 2);
		int countChar = countCharLenght(regex);
		if (countChar < 1) throw LekserException("oczekiwano liczby dodatniej w wyra¿eniu {x,y}");

		RegexNode* newTree(new  RegexNode());
		newTree = addQuestion(previewElement, regex, tree, id);
		for (int i = 1; i < countChar; ++i)
		{
			newTree = addCombine(previewElement, element, newTree, id);
			newTree = addQuestion(previewElement, regex, newTree, id);
		}
		regex.erase(0, 1);
		return newTree;
	}
	regex.erase(0, 1);
	int countChar = countCharLenght(regex);
	if (countChar < 1) throw LekserException("oczekiwano liczby dodatniej w wyra¿eniu {x,y}");
	RegexNode* newTree(new  RegexNode(tree, nullptr));
	for (int i = 1; i < countChar; ++i)
	{
		newTree = addCombine(previewElement, element, newTree, id);
	}
	if (regex[0] == ',')
	{
		regex.erase(0, 1);
		int maxCountChar = countCharLenght(regex);
		if (maxCountChar == -1)
		{
			regex.erase(0, 1);
			newTree = addCombine(previewElement, element, newTree, id);
			newTree = addStar(previewElement, element, newTree, id);
			return newTree;
		}
		if (maxCountChar < 1) throw LekserException("oczekiwano liczby dodatniej w wyra¿eniu {x,y}");

		int countCharToExecute = maxCountChar - countChar;

		for (int i = 0; i < countCharToExecute; ++i)
		{
			newTree = addCombine(previewElement, element, newTree, id);
			newTree = addQuestion(previewElement, element, newTree, id);
		}
	}
	return newTree;
}

Lex::RegexNode* Lex::RegexConstructorSyntaxTree::addBlock(PreviewElement previewElement, std::string& regex, RegexNode* tree, int& id)
{
	std::string index = "";
	int i = 1;
	for (; regex[i] != ']'; ++i)
	{
		if (i == regex.length() - 1) throw LekserException("oczekiwano ]");
		index += regex[i];
	}
	if (index.length() < 1)throw LekserException("brak wartoœci w bloku []");
	regex.erase(0, i);

	if (tree->getType() == RegexNodeType::BLOCK)
	{
		RegexNode* newTree(new  RegexNode(*tree));
		newTree->setBlockId(index);
		newTree->setId(id);
		id += 1;
		return newTree;
	}
	RegexNode* newTree(new  RegexNode());
	newTree->setFirstChild(tree);
	newTree->setId(id);
	id += 1;
	newTree->setType(RegexNodeType::COMBINE);
	RegexNode* secondChild(new  RegexNode);
	secondChild->setType(RegexNodeType::BLOCK);
	secondChild->setBlockId(index);
	secondChild->setId(id);
	id += 1;
	newTree->setSecondChild(secondChild);
	return newTree;
}

int Lex::RegexConstructorSyntaxTree::countCharLenght(std::string& regex)
{
	std::string number = "";
	while (regex[0] != '}' && regex[0] != ',')
	{
		number += regex[0];
		regex.erase(0, 1);
	}
	if (number.length() < 1) return -1;
	return std::stoi(number);
}