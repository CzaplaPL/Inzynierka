#include <iostream>
#include "Lekser++.h"
#define DEBUG true
#define ENV "dev"

int main()
{
	Lekser lex("tekst.txt");
	std::vector<std::string> test = lex.analizeFile("test.txt");
	int c = 0;
	return 1;
}