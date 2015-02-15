#include "BuildingManagerEntity.h"
#include "BuildingComponent.h"

BuildingManagerEntity::BuildingManagerEntity() : GameEnvironmentEntity("BuildingManager")
{
}


BuildingManagerEntity::~BuildingManagerEntity(void)
{
}


void BuildingManagerEntity::onStart()
{
}

void BuildingManagerEntity::onUpdate()
{
	std::cout << "BuildingManager sie kurwa update'uje!!!!!!!!!!\n";
}

void BuildingManagerEntity::onStop()
{
}

GameObject* BuildingManagerEntity::create()
{
	GameObject* retVal = new GameObject();
	retVal->setName("TestBuilding");
	retVal->addComponent(new BuildingComponent());
	return retVal;
}

void BuildingManagerEntity::add(GameObject* building)
{
	GameEngine::engine()->currentScene->addObject(building);
	_buildings.push_back(building);
}

void BuildingManagerEntity::remove(GameObject* building)
{
	GameEngine::engine()->currentScene->removeObject(building);
	for(int i = 0; i < _buildings.size(); i++)
	{
		if(_buildings[i] == building)
		{
			_buildings.erase(_buildings.begin() + i);
			return;
		}
	}
}

std::vector<GameObject*> BuildingManagerEntity::getBuildings()
{
    return _buildings;
}

std::vector<Workplace*> BuildingManagerEntity::getWorkplaces()
{
    std::vector<Workplace*> retVal;
    for(auto building : _buildings)
    {
        BuildingComponent *currComp = (BuildingComponent*)building->findComponent("BuildingComponent");
        retVal.insert(retVal.begin(), currComp->workplaces.begin(), currComp->workplaces.end());
    }
    return retVal;
}