#include "IdCreator.h"

void IdCreator::clearMap()
{
	this->stepIds.clear();
}

string IdCreator::generateId(const vector<int>& vector)
{
	string vectorId = "";
	for (int const element : vector)
	{
		vectorId += to_string(element) + "-";
	}
	if (this->stepIds.find(vectorId) == this->stepIds.end())
	{
		string newId = Uuid::generateUUID();
		this->stepIds.insert_or_assign(vectorId, newId);
		return newId;
	}
	return this->stepIds[vectorId];
}

string IdCreator::generateId(const vector<string>& vector)
{
	string vectorId = "";
	for (string element : vector)
	{
		vectorId += element + "-";
	}
	if (this->stepIds.find(vectorId) == this->stepIds.end())
	{
		string newId = Uuid::generateUUID();
		this->stepIds.insert_or_assign(vectorId, newId);
		return newId;
	}
	return this->stepIds[vectorId];
}