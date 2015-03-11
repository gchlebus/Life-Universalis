//
//  HumanAIWorkNeedComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 10/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanAIWorkNeedComponent.h"
#include "BuildingComponent.h"
#include "HumanIncludes.h"
#include "Workplace.h"

HumanAIWorkNeedComponent::HumanAIWorkNeedComponent() : HumanAINeedComponent("Work")
{
    
}

void HumanAIWorkNeedComponent::onUpdate()
{
    HumanAINeedComponent::onUpdate();
}

std::string HumanAIWorkNeedComponent::getNeedName()
{
    return "Work";
}

void HumanAIWorkNeedComponent::updatePriority()
{
    if(_humanComponent->getWorkplace() == nullptr)
    {
        _priority = 0.0;
        _progress = 0.0;
        return;
    }
    GameDate startWork = estimateNextWorkStart();
    GameDate currentTime = ((DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME))->getCurrentGameDate();
    
    double minutesLeft = startWork.time - currentTime.time;
    Vector3 pos = _parent->getTransform().getWorldPosition();
    Vector3 building = _humanComponent->getWorkplace()->parent->getParent()->getTransform().getWorldPosition();
    float timeNeededToTravel = _humanComponent->humanMotion->getSpeed() * (pos - building).norm();
    float timeDiff = minutesLeft - timeNeededToTravel;
    
    
    
    std::cout << "Human work stats:\n";
    std::cout << "\tMinutes needed to travel to work: " << timeNeededToTravel << "\n";
    std::cout << "\tHours to start working: " << minutesLeft / 60.0 << "\n";
    std::cout << "\tMinutes to start working: " << minutesLeft << "\n";
    std::cout << "\tI have to hit the road in " << timeDiff << " minutes (if it's minus I'll be so late!)\n";
    _priority = 100.0;
    _progress = 0.0;
}

GameDate HumanAIWorkNeedComponent::estimateNextWorkStart()
{
    GameDate current = ((DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME))->getCurrentGameDate();
    
    double workStart = _humanComponent->getWorkplace()->startHour;
    double diff = workStart - current.getDayHour();
    
    if(diff >= 0)
        return GameDate(current.time + diff);
    return GameDate(current.time + diff + 1.0 * GD_DAY);
}