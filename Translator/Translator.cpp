#include <iostream>
#include <sstream>
#include "Lekser++.h"
#define DEBUG true
#define ENV "dev"

void zad1()
{
	Lekser lex("zad1_reguly.txt");

	int numOperators = 0;
	int numInts = 0;
	int numDoubles = 0;
	int numBrackets = 0;
	int intValue = 0;
	double doubleValue = 0.0;

	lex.addCallback("dec_num", [&numInts, &intValue](std::string value) -> void {
		std::cout << "liczba dziesietna " << value << std::endl;
		numInts += 1;
		intValue += std::stoi(value);
		});
	lex.addCallback("hex_num", [&numInts, &intValue](std::string value) -> void {
		std::cout << "liczba szesnastkowa " << value << std::endl;
		numInts += 1;
		intValue += std::stoul(value, nullptr, 16);
		});
	lex.addCallback("double_num", [&numDoubles, &doubleValue](std::string value) -> void {
		std::cout << "liczba rzeczywista (standardowa) " << value << std::endl;
		numDoubles += 1;
		doubleValue += std::stof(value);
		});
	lex.addCallback("double_exp_num", [&numDoubles, &doubleValue](std::string value) -> void {
		std::cout << "liczba rzeczywista (wykładnicza) " << value << std::endl;
		numDoubles += 1;
		std::istringstream os(value);
		double d;
		os >> d;
		doubleValue += d;
		});
	lex.addCallback("operator", [&numOperators](std::string value) -> void {
		std::cout << "operator " << value << std::endl;
		numOperators += 1;
		});
	lex.addCallback("op_bracket", [&numBrackets](std::string value) -> void {
		std::cout << "nawias otwierajacy " << value << std::endl;
		numBrackets += 1;
		});
	lex.addCallback("cl_bracket", [&numBrackets](std::string value) -> void {
		std::cout << "nawias zamykajacy " << value << std::endl;
		numBrackets += 1;
		});
	lex.analizeFile("zad1_test.txt");
	std::cout << "zliczono int  " << numInts << " o sumie = " << intValue << std::endl;
	std::cout << "zliczono double " << numDoubles << " o sumie = " << doubleValue << std::endl;
	std::cout << "zliczono operatorow " << numOperators << std::endl;
	std::cout << "zliczono nawiasow " << numBrackets << std::endl;
}

void zad2()
{
}

int main()
{
	//std::vector<std::pair<std::string, std::string>> m{ {"A","a"}, {"Aaa","abbc"}, {"ab","a*b"}, {"reg","(a|b)*abb"}, {"mi","mi"}, };
	//Lekser lex(/*"tekst.txt"*/m);
	//lex.setToken("cos", "$mi$kos", [](std::string value) -> void { std::cout << value << std::endl; });
	//lex.addCallback("cos", [](std::string value) -> void { std::cout << "new = " << value << std::endl; });
	//std::vector<std::string> test = lex.analize("a aaaab mikos \nbbbbbabb mikos");
	zad1();
	zad2();

	return 1;
}