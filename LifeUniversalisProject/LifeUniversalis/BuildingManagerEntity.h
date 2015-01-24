#pragma once

#include "GlobalHeaders.h"
#include "GameEnvironmentEntity.h"

class GameObject;

class BuildingManagerEntity : public GameEnvironmentEntity
{
public:
	BuildingManagerEntity();
	~BuildingManagerEntity();

	void onStart();
	void onUpdate();
	void onStop();

	GameObject* create();
	void add(GameObject* building);
	void remove(GameObject* building);

	std::vector<GameObject*> getBuildings();
protected:
	std::vector<GameObject*> _buildings;
};

