#pragma once

#include"addons/ILogger.h"
#include"addons/Logger.h"
#include"Das/DasService.h"
#include "sys/LekserDefinitionReader.h"

class __declspec(dllexport) Lekser
{
	std::shared_ptr<ILogger> log;
	std::unique_ptr<Lex::LekserDefinitionReader> definitionReader;
	std::unique_ptr<Lex::DasService> DasServices;
	std::vector<Lex::Definition> definitions;
	Lex::Das das;
	void init();
public:
	Lekser();
	Lekser(std::string file);
	Lekser(std::string file, ILogger* log);
	void generateLexer(std::string file);
	std::vector <std::string> analizeFile(std::string file);
	std::string toString();
};