#pragma once

#include"addons/ILogger.h"
#include"addons/Logger.h"

#include "sys/LekserDefinitionReader.h"

class __declspec(dllexport) Lekser
{
	std::shared_ptr<ILogger> log;
	std::unique_ptr<Lex::LekserDefinitionReader> definitionReader;
	void init();
public:
	Lekser();
	Lekser(std::string file);
	Lekser(std::string file, ILogger* log);
	void generateLexer(std::string file);
	;
	std::string toString();
};