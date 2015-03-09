

#include "BuildingManagerEntity.h"
#include "BuildingComponent.h"
#include "Workplace.h"

BuildingManagerEntity::BuildingManagerEntity() : GameEnvironmentEntity(EN_BUILDING_MGR)
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

std::vector<Workplace*> BuildingManagerEntity::getWorkplaces(bool onlyOffers)
{
    std::vector<Workplace*> retVal;
    for(auto building : _buildings)
    {
        BuildingComponent *currComp = (BuildingComponent*)building->findComponent("BuildingComponent");
        if(onlyOffers)
        {
            for(auto workplace : currComp->workplaces)
                if(workplace->isOffer)
                    retVal.push_back(workplace);
        }
        else
            retVal.insert(retVal.begin(), currComp->workplaces.begin(), currComp->workplaces.end());
    }
    return retVal;
}