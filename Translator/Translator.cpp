#include <iostream>

#include "addons/Logger.h"
#define DEBUG true
#define ENV "ddd"

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);
	log.info("info");
	log.writeDebug("si", "test ", 1);
	log.error("test error");
	cin.get();
}