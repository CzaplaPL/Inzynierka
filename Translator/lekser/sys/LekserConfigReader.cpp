#include "LekserConfigReader.h"

LekserConfigReader::LekserConfigReader(ILogger& log)
{
	this->log = &log;
}

bool LekserConfigReader::readConfig(fstream& file)
{
	string token;
	string regex;
	char separator;
	while (!file.eof())
	{
		file >> token >> separator >> regex;
		if (separator != ':')
		{
			log->error("b³ad odczytywania pliku z tokenami");
			return false;
		}
		log->writeDebug("ssscss", "token = ", token.c_str(), "  separator = ", separator, " regex = ", regex.c_str());
		this->readData.emplace_back(token, regex);
	}
	return true;
}