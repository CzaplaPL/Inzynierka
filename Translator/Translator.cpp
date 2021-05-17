
#include <iostream>
#include "Logger.h"

#define DEBUG true
#define ENV "dev"

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);
	log.writeDebug("si", "test ", 1);
	log.error("test error");
}
