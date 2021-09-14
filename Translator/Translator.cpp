#include <iostream>

#include "addons/Logger.h"
#define DEBUG true
#define ENV "ddd"

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);
	cin.get();
}