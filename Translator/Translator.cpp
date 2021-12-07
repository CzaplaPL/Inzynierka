#include <iostream>

#include "Lekser++.h"

#define DEBUG true
#define ENV "dev"

int main()
{
	Lex::Logger log(ENV);
	log.setDebug(DEBUG);

	Lekser* lekser = new Lekser(&log);
	Lekser* lekser2 = new Lekser();
	cin.get();
}