#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Lekser++.h"
#include <iostream>
void Lekser::init()
{
	this->definitionReader = std::make_unique<Lex::LekserDefinitionReader>((this->log));
	this->DasServices = std::make_unique<Lex::DasService>((this->log));
	this->lekserAnalizer = std::make_unique<Lex::LekserAnalizer>(this->log, &(this->das));
}

Lekser::Lekser()
{
	this->log.reset(new Lex::Logger("Lekser"));
	init();
}

Lekser::Lekser(std::string file)
{
	this->log.reset(new Lex::Logger("Lekser"));
	init();
	generateLexer(file);
}

Lekser::Lekser(std::string file, ILogger* log)
{
	this->log.reset(log);
	init();
	generateLexer(file);
}

void Lekser::generateLexer(std::string file)
{
	try {
		this->definitions = this->definitionReader->readDefinition(file);
	}
	catch (LekserReaderException exception)
	{
		this->log->error(exception.what());
		return;
	}
	this->das = this->DasServices->generateLekser(this->definitions);
}

std::vector<std::string> Lekser::analizeFile(std::string file)
{
	return this->lekserAnalizer->analizeFile(file);
}

std::string Lekser::toString()
{
	return " ";
}