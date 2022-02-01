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
	std::vector<std::pair<std::string, std::string>> reguly{
		{"number","[1-9][0-9]*"},
		{"id","(([A-Z] | [a-z])([A-Z] | [a-z] | [0-9]))+"},
		{"output","OUTPUT"},
		{"add","ADD"},
		{"subt","SUBT"},
		{"load","LOAD"},
		{"store","STORE"},
		{"clear","CLEAR"},
		{"halt","HALT"},
		{"var","VAR"},
		{"comment","//"},
		{"input","INPUT"},
		{"newLine","\n"},
	};

	bool komentarz = false;
	std::map<std::string, std::function<void(std::string)>> wywolaniaZwrotne{
		{"newLine" , [&komentarz](std::string value) -> void {komentarz = false; }},
		{"comment" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "komentarz" << std::endl;
			komentarz = true;
			}
		},
		{"input" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "czytanie z rejestru wejsciowego" << std::endl;
			}
		},
		{"output" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "pisanie do rejestru wyjściowego" << std::endl;
			}
		},
		{"add" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "dodawanie do akumulatora" << std::endl;
			}
		},
		{"subt" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "odejmowanie od akumulatora" << std::endl;
			}
		},
		{"load" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "wczytanie z pamieci" << std::endl;
			}
		},
		{"store" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "zapisanie do pamieci" << std::endl;
			}
		},
		{"clear" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "zerowanie akumulatora" << std::endl;
			}
		},
		{"halt" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "zatrzymanie programu" << std::endl;
			}
		},
		{"var" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "deklaracja zmiennej" << std::endl;
			}
		},
		{"id" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "zmienna: " << value << std::endl;
			}
		},
		{"number" , [&komentarz](std::string value) -> void {
			if (!komentarz) std::cout << "adres: " << value << std::endl;
			}
		},
	};

	Lekser lex(reguly, wywolaniaZwrotne);

	lex.analizeFile("zad2_program.txt");
}

int main()
{
	zad1();
	zad2();

	return 1;
}