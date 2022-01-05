#include "IdCreator.h"

namespace Lex
{
	void IdCreator::clearMap()
	{
		this->stepIds.clear();
	}

	std::string IdCreator::generateId(const std::vector<int>& vector)
	{
		std::string vectorId = "";
		for (int const element : vector)
		{
			vectorId += std::to_string(element) + "-";
		}
		if (this->stepIds.find(vectorId) == this->stepIds.end())
		{
			std::string newId = Uuid::generateUUID();
			this->stepIds.insert_or_assign(vectorId, newId);
			return newId;
		}
		return this->stepIds[vectorId];
	}

	std::string IdCreator::generateId(const std::vector<std::string>& vector)
	{
		std::string vectorId = "";
		for (std::string element : vector)
		{
			vectorId += element + "-";
		}
		if (this->stepIds.find(vectorId) == this->stepIds.end())
		{
			std::string newId = Uuid::generateUUID();
			this->stepIds.insert_or_assign(vectorId, newId);
			return newId;
		}
		return this->stepIds[vectorId];
	}
}