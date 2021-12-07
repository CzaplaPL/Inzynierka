#include "Lekser++.h"

Lekser::Lekser()
{
	this->log = new Lex::Logger("Lekser");
	//this->configReader = LekserConfigReader(this->log);
	this->log->error("lekser2");
}

Lekser::Lekser(ILogger* log)
{
	this->log = log;
	this->log->error("lekser1");
}