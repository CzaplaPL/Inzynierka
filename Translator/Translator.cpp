#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>

#include <iostream>

#include "Lekser++.h"
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define new MYDEBUG_NEW
#define DEBUG true
#define ENV "dev"

int main()
{
	Lekser lex("tekst.txt");

	Lex::Logger llo("cos");
	Lex::RegexService ser(llo);

	string reg = "a|[a-b]";
	int id = 0;
	Lex::RegexNode* node = ser.generateTree(reg, id);
	delete node;
	cin.get();
	_CrtDumpMemoryLeaks();

	return 1;
}