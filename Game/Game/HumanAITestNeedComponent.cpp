//
//  HumanAITestNeedComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanAITestNeedComponent.h"
#include "DayTimeEntity.h"
#include "BuildingManagerEntity.h"
#include "BuildingComponent.h"
#include "Service.h"
#include "HumanIncludes.h"
#include "Queue.h"


HumanAITestNeedComponent::HumanAITestNeedComponent()
: HumanAINeedComponent("Test")
{
    _fulfillment = 1.0;
    buildingManager = (BuildingManagerEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_BUILDING_MGR);
    state = HAIT_IDLE;
}

HumanAITestNeedComponent::~HumanAITestNeedComponent()
{
}

void HumanAITestNeedComponent::onUpdate()
{
    if(state == HAIT_IDLE)
    {
        computeBestService();
        if(bestService != nullptr)
        {
            state = HAIT_GOING;
            _humanComponent->humanMotion->setTargetPosition(bestService->getParent()->getParent()->getTransform().getWorldPosition());
        }
    }
    else if(state == HAIT_GOING)
    {
        if(_humanComponent->humanMotion->isAtTargetPosition())
        {
            if(bestService->getParent()->queue->enter(myQueueIndex, true))
            {
                state = HAIT_WAITING_IN_QUEUE;
            }
        }
    }
    else if(state == HAIT_WAITING_IN_QUEUE)
    {
        
    }
    //Just for tests
//    for(auto e : services)
//        std::cout <<"Found service!\n\tRating: " << e.second << "\n";
}

void HumanAITestNeedComponent::onEnabled()
{
    LOG("Test is turned on!");
    state = HAIT_IDLE;
}

void HumanAITestNeedComponent::onDisabled()
{
    LOG("Test is turned off!");
}

std::string HumanAITestNeedComponent::getNeedName()
{
    return "Test";
}

void HumanAITestNeedComponent::computeBestService()
{
    bestService = nullptr;
    std::vector<GameObject*> buildings = buildingManager->getBuildings();
    std::list<std::pair<Service*, float>> services;
    
    Transform* t = &_parent->getTransform();
    for(auto building : buildings)
    {
        BuildingComponent* comp = (BuildingComponent*)building->findComponent("BuildingComponent");
        float serviceValue = comp->service->getAttributeValue(this->getNeedName());
        if(serviceValue > 0.0)
        {
            float distance = 0.0;
            Vector3 pos = t->getWorldPosition();
            Vector3 buildingPos = comp->getParent()->getTransform().getWorldPosition();
            Vector3 dist = pos - buildingPos;
            distance = dist.norm();
            
            float rating = serviceValue * 100.0 - (distance*distance)*0.0001;
            services.insert(services.end(), std::make_pair(comp->service, rating));
        }
    }
    services.sort([&](std::pair<Service*, float> &first, std::pair<Service*, float> &second)
                  {
                      return first.second >= second.second;
                  });

    if(services.size() != 0)
        bestService = services.front().first;
}

void HumanAITestNeedComponent::updateFulfillment()
{
    DayTimeEntity* dt = (DayTimeEntity*) GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME);

    //Per game-minute
    double progressModifier = 1.0 / 60.0;// / 24.0;
    _fulfillment -= dt->getLastDelta().time * progressModifier;
}

void HumanAITestNeedComponent::updatePriority()
{
    _priority = (1.0 - _fulfillment) * 90.0; //It shall never win against work need
}
