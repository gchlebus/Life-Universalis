#pragma once

#include "GlobalHeaders.h"
#include "GameEnvironmentEntity.h"

class GameObject;
class Workplace;

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
    std::vector<Workplace*> getWorkplaces();
protected:
	std::vector<GameObject*> _buildings;
};

