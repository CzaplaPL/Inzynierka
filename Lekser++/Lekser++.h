#pragma once

#include"addons/ILogger.h"
#include"addons/Logger.h"
#include"regex/RegexService.h"
#include"regex/RegexNode.h"

#include "sys/LekserDefinitionReader.h"

class __declspec(dllexport) Lekser
{
	std::shared_ptr<ILogger> log;
	std::unique_ptr<Lex::LekserDefinitionReader> definitionReader;
	void init();
public:
	Lekser();
	Lekser(string file);
	Lekser(string file, ILogger* log);
	void generateLexer(string file);
	void test(string file);
	string toString();
};