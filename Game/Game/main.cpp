#include "DayTimeEntity.h"
#include "HumanManagerEntity.h"
#include "BuildingManagerEntity.h"


#include "Workplace.h"
#include "BuildingComponent.h"

#include <GameEngine.h>

int main()
{
    GameEngine *e = GameEngine::engine();
    
    HumanManagerEntity* humanMgr = new HumanManagerEntity();
    BuildingManagerEntity* buildingMgr = new BuildingManagerEntity();
    DayTimeEntity* dayTime = new DayTimeEntity();

    //temporary scene initailization
    //It produces memory leak!!! Just for test use!!!
    e->currentEnvironment = new GameEnvironment();
    e->currentEnvironment->addEntity(dayTime);
    e->currentEnvironment->addEntity(humanMgr);
    e->currentEnvironment->addEntity(buildingMgr);

    e->currentScene = new Scene();
    
    
    for(int i = 0; i < 100; i++)
    {
        GameObject* human = humanMgr->create();
        humanMgr->add(human);
    }
    for(int i = 0; i < 10; i++)
    {
        GameObject* building = buildingMgr->create();
        BuildingComponent* buildingComp = (BuildingComponent*)building->findComponent("BuildingComponent");
        for(int w = 0; w < 10; w++)
        {
            Workplace* workplace = new Workplace();
            workplace->parent = buildingComp;
            workplace->isOffer = true;
            workplace->startHour = 8.0 + w;
            workplace->salary = 100.0 + w * 100.0;
            buildingComp->workplaces.push_back(workplace);
        }
        buildingMgr->add(building);
    }
    
    
//    for (int i = 0; i < 100000; ++i)
//    {
//        e->currentScene->addObject(new GameObject());
//    }

    e->run();
    e->tempJoin();

    return 0;
}