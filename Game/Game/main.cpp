#include "DayTimeEntity.h"
#include "HumanManagerEntity.h"
#include "BuildingManagerEntity.h"

#include "Workplace.h"
#include "BuildingComponent.h"
#include "Service.h"

#include <GameEngine.h>

int main()
{
    GameEngine *e = GameEngine::engine();
    
    HumanManagerEntity* humanMgr        = new HumanManagerEntity();
    BuildingManagerEntity* buildingMgr  = new BuildingManagerEntity();
    DayTimeEntity* dayTime              = new DayTimeEntity();

    e->currentEnvironment = new GameEnvironment();
    e->currentEnvironment->addEntity(dayTime);
    e->currentEnvironment->addEntity(humanMgr);
    e->currentEnvironment->addEntity(buildingMgr);

    e->currentScene = new Scene();
    
    //10 buildings, 10 workplaces per building, 100 worklpaces in total
    //200 people, 100 of them are supposed to be unemployed
    //Test is running at 5th game minute, look at console output
    //Test is implemented in HumanManagerEntity
    for(int i = 0; i < 200; i++)
    {
        GameObject* human = humanMgr->create();
        human->getTransform().setWorldPosition(Vector3((float)i * 10.0, 0.0, 100.0));
        humanMgr->add(human);
    }
    for(int i = 0; i < 10; i++)
    {
        GameObject* building = buildingMgr->create();
        building->getTransform().setWorldPosition(Vector3((float)i * 10.0, 0.0, 0.0));
        BuildingComponent* buildingComp = (BuildingComponent*)building->findComponent("BuildingComponent");
        buildingComp->service->addAttribute("Test", (float)i);
        for(int w = 0; w < 10; w++)
        {
            Workplace* workplace = new Workplace();
            workplace->parent = buildingComp;
            workplace->isOffer = true;
            workplace->startHour = 0.1 + w;
            workplace->salary = 100.0 + w * 100.0;
            buildingComp->workplaces.push_back(workplace);
        }
        buildingMgr->add(building);
    }

    e->run();
    e->tempJoin();

    return 0;
}