#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Lekser++.h"
#include <iostream>
void Lekser::init()
{
	this->definitionReader = make_unique<Lex::LekserDefinitionReader>((this->log));
}

Lekser::Lekser()
{
	this->log.reset(new Lex::Logger("Lekser"));
	init();
}

Lekser::Lekser(string file)
{
	this->log.reset(new Lex::Logger("Lekser"));
	init();
	generateLexer(file);
}

Lekser::Lekser(string file, ILogger* log)
{
	this->log.reset(log);
	init();
	generateLexer(file);
}

void Lekser::generateLexer(string file)
{
	try {
		std::map<std::string, std::string> definitions = this->definitionReader->readDefinition(file);
	}
	catch (LekserReaderException exception)
	{
		this->log->error(exception.what());
	}
}

void Lekser::test(string file)
{
	Lex::Logger llo("cos");
	Lex::RegexService ser(llo);

	string reg = "a|[a-b]";
	int id = 0;
	Lex::RegexNode* node = ser.generateTree(reg, id);
	delete node;
}

string Lekser::toString()
{
	return " ";
}