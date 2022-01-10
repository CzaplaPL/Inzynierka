#include "Lekser++.h"

void Lekser::init()
{
	this->definitionReader = std::make_unique<Lex::LekserDefinitionReader>((this->log));
	this->DasServices = std::make_unique<Lex::DasService>((this->log));
	this->lekserAnalizer = std::make_unique<Lex::LekserAnalizer>(this->log, &(this->das));
}

Lekser::Lekser()
{
	this->log.reset(new  Lex::Logger("Lekser"));
	init();
}

Lekser::Lekser(std::string file)
{
	this->log.reset(new  Lex::Logger("Lekser"));
	init();
	generateLexer(file);
}

Lekser::Lekser(std::string file, std::map<std::string, std::function<void(std::string)>> callbacks)
{
	this->log.reset(new  Lex::Logger("Lekser"));
	init();
	generateLexer(file);
	this->addCallbacks(callbacks);
}

Lekser::Lekser(std::string file, ILogger* log)
{
	this->log.reset(log);
	init();
	generateLexer(file);
}

Lekser::Lekser(std::string file, ILogger* log, std::map<std::string, std::function<void(std::string)>> callbacks)
{
	this->log.reset(log);
	init();
	generateLexer(file);
	this->addCallbacks(callbacks);
}

Lekser::Lekser(std::vector<std::pair<std::string, std::string>> tokenMap)
{
	this->log.reset(new  Lex::Logger("Lekser"));
	init();
	generateLexer(tokenMap);
}

Lekser::Lekser(std::vector<std::pair<std::string, std::string>> tokenMap, ILogger* log)
{
	this->log.reset(log);
	init();
	generateLexer(tokenMap);
}

Lekser::Lekser(std::vector<std::pair<std::string, std::string>> tokenMap, ILogger* log, std::map<std::string, std::function<void(std::string)>> callbacks)
{
	this->log.reset(log);
	init();
	generateLexer(tokenMap);
	this->addCallbacks(callbacks);
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

void Lekser::setToken(std::string token, std::string regex, std::function<void(std::string)> foo)
{
	this->setToken(token, regex);
	this->das.addCallbackFunction(token, foo);
}

std::vector<std::pair<std::string, std::string>> Lekser::getTokensMap()
{
	return std::vector<std::pair<std::string, std::string>>();
}

void Lekser::addCallback(std::string token, std::function<void(std::string)> callback)
{
	this->das.addCallbackFunction(token, callback);
}

void Lekser::addCallbacks(std::map<std::string, std::function<void(std::string)>> callbacks)
{
	for (auto element : callbacks)
	{
		this->das.addCallbackFunction(element.first, element.second);
	}
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