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


HumanAITestNeedComponent::HumanAITestNeedComponent()
: HumanAINeedComponent("Test")
{
    _progress = 1.0;
}

HumanAITestNeedComponent::~HumanAITestNeedComponent()
{
}

void HumanAITestNeedComponent::onStart()
{
}

void HumanAITestNeedComponent::onBeforeFirstUpdate()
{
}

void HumanAITestNeedComponent::onUpdate()
{
    BuildingManagerEntity* bm = (BuildingManagerEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_BUILDING_MGR);
    
    std::vector<GameObject*> buildings = bm->getBuildings();
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
    
    //Just for tests
//    for(auto e : services)
//        std::cout <<"Found service!\n\tRating: " << e.second << "\n";
}

void HumanAITestNeedComponent::onAttachToParent()
{
}

void HumanAITestNeedComponent::onDetachFromParent()
{
}

void HumanAITestNeedComponent::onDelete()
{
}
void HumanAITestNeedComponent::onEnabled()
{
}
void HumanAITestNeedComponent::onDisabled()
{
}

void HumanAITestNeedComponent::updatePriority()
{
    DayTimeEntity *dt = (DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME);
    
    //Per game-minute
    double progressModifier = 1.0 / 60.0;// / 24.0;
    _progress -= dt->getLastDelta().time * progressModifier;
    
    _priority = (1.0 - _progress) * 100.0;
}
std::string HumanAITestNeedComponent::getNeedName()
{
    return "Test";
}