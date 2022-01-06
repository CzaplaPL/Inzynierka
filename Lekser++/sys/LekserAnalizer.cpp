#include "LekserAnalizer.h"

std::vector<std::string> Lex::LekserAnalizer::analizeFile(std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		this->log->error("nie uda³o otworzyc pliku z definicjami : " + fileName);
		return std::vector<std::string>();
	}
	std::string line;
	int numberLine = 0;
	while (std::getline(file, line))
	{
	}
	return std::vector<std::string>();
}