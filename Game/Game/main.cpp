#include "DayTimeEntity.h"
#include "HumanManagerEntity.h"
#include "BuildingManagerEntity.h"

#include "HumanComponent.h"
#include "PaymentAgentComponent.h"

#include "Workplace.h"
#include "BuildingComponent.h"
#include "Service.h"


#include "HumanComponentNames.h"
#include "ServicePoint.h"
#include "Queue.h"
#include "Machine.h"

#include <GameEngine.h>

int main()
{
    GameEngine *e = GameEngine::engine();
    e->kernel->logger->addLogger(new ConsoleLogger());
    
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
    
    HumanComponent *hc0 = (HumanComponent*)humanMgr->getHumans()[0]->findComponent(HC_MAIN);
    
    for(int i = 0; i < 10; i++)
        hc0->paymentAgent->bookPayment(50 + i, hc0->paymentAgent, "Test payment");
    
    for(int i = 0; i < 10; i++)
    {
        GameObject* building = buildingMgr->create();
        building->getTransform().setWorldPosition(Vector3((float)i * 10.0, 0.0, 0.0));
        BuildingComponent* buildingComp = (BuildingComponent*)building->findComponent("BuildingComponent");

        Service* service = new Service("Kielbaska");
        service->setMinimalWorkplaceOccupation(2);
        service->setUsageTime(2, 30);
        service->setUsageTime(3, 10);
        service->setFulfillmentChange("Satiety", 0.3);
        service->setPrice(20);

        ServicePoint* servicePoint = new ServicePoint(service, new Queue(), 5);
        for (int w = 0; w < 5; w++)
        {
            Workplace* workplace = servicePoint->getWorkplaces()[w];
            workplace->parent = buildingComp;
            workplace->startHour = 0.5 + (float)w * 0.5;
            workplace->salary = 100.0 + (10 - w) * 100.0;
        }

        Machine* machine = new Machine();
        machine->addServicePoint(servicePoint);

        buildingComp->addMachine(machine);
        buildingMgr->add(building);
    }

    e->run();
    e->tempJoin();

    return 0;
}