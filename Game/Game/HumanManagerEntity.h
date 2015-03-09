#pragma once

#include <GameEngine.h>
#include "EnvironmentEntitiesNames.h"

class HumanManagerEntity : public GameEnvironmentEntity
{
public:
	HumanManagerEntity();
	~HumanManagerEntity();

	void onStart();
	void onUpdate();
	void onStop();

	GameObject* create();
	void add(GameObject* human);
	void remove(GameObject* human);

	std::vector<GameObject*> getHumans();
protected:
	std::vector<GameObject*> _humans;
};

