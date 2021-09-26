#include <iostream>

#include "addons/Logger.h"
#define DEBUG true
#define ENV "dev"

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);
	cin.get();
}