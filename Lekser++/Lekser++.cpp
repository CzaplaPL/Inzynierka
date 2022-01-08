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

Lekser::Lekser(std::vector<std::pair<std::string, std::string>> tokenMap)
{
	this->log.reset(new Lex::Logger("Lekser"));
	init();
	generateLexer(tokenMap);
}

Lekser::Lekser(std::vector<std::pair<std::string, std::string>> tokenMap, ILogger* log)
{
	this->log.reset(log);
	init();
	generateLexer(tokenMap);
}

void Lekser::generateLexer(std::vector<std::pair<std::string, std::string>> tokenMap)
{
	this->definitions.clear();
	this->definitions = this->definitionReader->definitionfromMap(tokenMap);
	this->das = this->DasServices->generateLekser(this->definitions);
}

void Lekser::generateLexer(std::string file)
{
	try
	{
		this->definitions = this->definitionReader->readDefinition(file);
	}
	catch (LekserReaderException exception)
	{
		this->log->error(exception.what());
	}
	this->das = this->DasServices->generateLekser(this->definitions);
}

void Lekser::setToken(std::string token, std::string regex)
{
	try
	{
		this->definitions = this->definitionReader->addDefinition(token, regex);
	}
	catch (LekserReaderException exception)
	{
		this->log->error(exception.what());
	}
	this->das = this->DasServices->generateLekser(this->definitions);
}

std::vector<std::string> Lekser::analizeFile(std::string file)
{
	return this->lekserAnalizer->analizeFile(file);
}

std::vector<std::string> Lekser::analize(std::string text)
{
	return this->lekserAnalizer->analize(text);
}

std::string Lekser::toString()
{
	return " ";
}