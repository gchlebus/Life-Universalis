//
//  HumanAINeedComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanAINeedComponent.h"
#include "Service.h"

HumanAINeedComponent::HumanAINeedComponent(const std::string& name)
    : GameObjectComponent("HumanAINeed" + name), _lastUpdateTime(0.), _canBeCancelled(true)
{
    GameEnvironmentEntity* e = GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME);
    assert(e != nullptr);
    _dayTime = static_cast<DayTimeEntity*>(e);
}

HumanAINeedComponent::~HumanAINeedComponent()
{
}

bool HumanAINeedComponent::canBeCancelled()
{
    return _canBeCancelled;
}

void HumanAINeedComponent::updateStats()
{
    updateFulfillment();
    _fulfillment = boost::algorithm::clamp(_fulfillment, 0.0f, 1.0f);
    updatePriority();
    _priority = boost::algorithm::clamp(_priority, 0.0f, 100.0f);
    _lastUpdateTime = _dayTime->getCurrentGameDate().time;
}

float HumanAINeedComponent::getPriority()
{
    return _priority;
}

float HumanAINeedComponent::getFulfillment()
{
    return _fulfillment;
}

float HumanAINeedComponent::valueImpact(Service* product)
{
    if(product == nullptr)
    {
        return 0;
    }
    
    const float majorWeight =  2, minorWeight = 1;
    float sum = 0, weight = 0, currentWeight = minorWeight;
    
    HumanAINeedComponent *targetNeed = this;
    
    for(auto& attribute : product->getAttributeMap())
    {
        std::vector<GameObjectComponent*> affectedNeedComponents = _parent->findComponentsContainingString("HumanAINeed" + attribute.first);
        
        for(GameObjectComponent *comp : affectedNeedComponents)
        {
            HumanAINeedComponent *need  = (HumanAINeedComponent*)comp;
            
            currentWeight = (need->getComponentName() == targetNeed->getComponentName()) ? majorWeight : minorWeight;
            
            sum += attribute.second * currentWeight;
            weight += currentWeight;
        }
    }
    
    return weight > 0 ? sum / weight : 0;
}

void HumanAINeedComponent::onParentChangedComponents()
{
    _humanComponent = (HumanComponent*)_parent->findComponent("HumanComponent");
}