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
    //121 people, 21 of them are supposed to be unemployed
    //Test is running at 5th game minute, look at console output
    //Test is implemented in HumanManagerEntity
    int peopleWidth = 1;
    for(int i = 0; i < peopleWidth; i++)
    {
        for(int j = 0; j < peopleWidth; j++)
        {
            GameObject* human = humanMgr->create();
            human->getTransform().setWorldPosition(Vector3(i * 5.0, 0.0, j * 5.0) + Vector3(0, 0, -50));
            humanMgr->add(human);
        }
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
            workplace->startHour = 0.5 + (float)w * 0.5;
            workplace->salary = 100.0 + (10 - w) * 100.0;
            buildingComp->workplaces.push_back(workplace);
        }
        buildingMgr->add(building);
    }

    e->run();
    e->tempJoin();

    return 0;
}