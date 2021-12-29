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

string Lekser::toString()
{
	return " ";
}