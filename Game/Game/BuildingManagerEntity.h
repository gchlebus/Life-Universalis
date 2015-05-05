#pragma once

#include <GameEngine.h>
#include "EnvironmentEntitiesNames.h"
#include "Workplace.h"

class BuildingManagerEntity
    : public GameEnvironmentEntity
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

    Workplace::PtrVector getWorkplaces(bool onlyOffers);

protected:
    std::vector<GameObject*> _buildings;
};

