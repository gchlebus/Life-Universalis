#include "GameEnvironment.h"
#include "GameEnvironmentEntity.h"

GameEnvironment::GameEnvironment()
{
}
GameEnvironment::~GameEnvironment()
{
}

bool GameEnvironment::addEntity(GameEnvironmentEntity* entity)
{
	GameEnvironmentEntity *obj = findEntity(entity->getName());
	if(obj != nullptr)
		return false;
	_entities.push_back(entity);
	return false;
}
void GameEnvironment::removeEntity(GameEnvironmentEntity* entity)
{
	for(int i = 0; i < _entities.size(); i++)
	{
		if(_entities[i] == entity)
		{
			_entities.erase(_entities.begin() + i);
			return;
		}
	}
}

std::vector<GameEnvironmentEntity*> GameEnvironment::getEntities()
{
	return _entities;
}

GameEnvironmentEntity* GameEnvironment::findEntity(std::string name)
{
	for(int i = 0; i < _entities.size(); i++)
	{
		if(_entities[i]->getName() == name)
		{
			return _entities[i];
		}
	}
	return nullptr;
}