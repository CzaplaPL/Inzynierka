#include <iostream>

#include "pointerTest.h"
#include "addons/Logger.h"
#define DEBUG true
#define ENV "dev"

int f1() {
	return 1;
}

int f2() {
	return 2;
}

typedef int (*fptr)();

fptr f(char c) {
	if (c == '1') {
		return f1;
	}
	else {
		return f2;
	}
}

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);
	log.info("info");
	log.writeDebug("si", "test ", 1);
	log.error("test error");

	char c = '2';
	fptr fp = f(c);
	cout << fp() << endl;
}