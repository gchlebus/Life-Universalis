#pragma once
#include "GlobalHeaders.h"

class GameEnvironmentEntity;

class GAMEENGINE_EXPORT GameEnvironment
{
public:
	GameEnvironment();
	~GameEnvironment();

	bool addEntity(GameEnvironmentEntity* entity);
	void removeEntity(GameEnvironmentEntity* entity);

	std::vector<GameEnvironmentEntity*> getEntities();
	GameEnvironmentEntity* findEntity(std::string name);
protected:
	std::vector<GameEnvironmentEntity*> _entities;
};