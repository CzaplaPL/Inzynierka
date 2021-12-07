#include <iostream>

#include "addons/Logger.h"
#include "lekser/DAS/Das.h"
#include "lekser/DAS/DasService.h"
#include "lekser/regex/RegexNode.h"
#include "lekser/regex/RegexService.h"
#include "lekser/sys/LekserConfigReader.h"
#define DEBUG true
#define ENV "dev"

int main()
{
	Logger log(ENV);
	log.setDebug(DEBUG);

	Lekser* lekser = new Lekser(&log);
	/*fstream lekserConfig;
	lekserConfig.open("lekserConfig.leks", ios::in);
	if (!lekserConfig.is_open())log.error("nie udalo się otworzyć lekserConfig.leks");
	LekserConfigReader lekserConfigReader(log);
	lekserConfigReader.readConfig(lekserConfig);*/
	Lekser* lekser2 = new Lekser();
	cin.get();
}