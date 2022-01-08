#pragma once

#include"addons/ILogger.h"
#include"addons/Logger.h"
#include"Das/DasService.h"
#include "sys/LekserDefinitionReader.h"
#include "sys/LekserAnalizer.h"

class __declspec(dllexport) Lekser
{
	std::shared_ptr<ILogger> log;
	std::unique_ptr<Lex::LekserDefinitionReader> definitionReader;
	std::unique_ptr<Lex::DasService> DasServices;
	std::unique_ptr<Lex::LekserAnalizer> lekserAnalizer;
	std::vector<Lex::Definition> definitions;
	Lex::Das das;
	void init();
public:
	Lekser();
	Lekser(std::string file);
	Lekser(std::string file, ILogger* log);
	Lekser(std::vector<std::pair<std::string, std::string>> tokenMap);
	Lekser(std::vector<std::pair<std::string, std::string>> tokenMap, ILogger* log);
	void generateLexer(std::vector<std::pair<std::string, std::string>> tokenMap);
	void generateLexer(std::string file);
	void setToken(std::string token, std::string regex);
	std::vector <std::string> analizeFile(std::string file);
	std::vector <std::string> analize(std::string text);
	std::string toString();
};