#include <iostream>
#include "Lekser++.h"
#define DEBUG true
#define ENV "dev"

int main()
{
	std::vector<std::pair<std::string, std::string>> m{ {"A","a"}, {"Aaa","abbc"}, {"ab","a*b"}, {"reg","(a|b)*abb"}, {"mi","mi"}, };
	Lekser lex(/*"tekst.txt"*/m);
	lex.setToken("cos", "$mi$kos");
	std::vector<std::string> test = lex.analize("a aaaab abb \nbbbbbabb");
	int c = 0;
	return 1;
}