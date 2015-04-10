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

#include "HumanTaskQueueComponent.h"
#include "WorkHumanTask.h"

HumanAIWorkNeedComponent::HumanAIWorkNeedComponent() : HumanAINeedComponent("Work")
{
    _dayTime = (DayTimeEntity*) GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME);
    _currentTask = nullptr;
}

void HumanAIWorkNeedComponent::onEnabled()
{
    LOG("Work is turned on!");
}

void HumanAIWorkNeedComponent::onDisabled()
{
    LOG("Work is turned off!");
}

void HumanAIWorkNeedComponent::onAttachToParent()
{

}

void HumanAIWorkNeedComponent::onUpdate()
{
    HumanAINeedComponent::onUpdate();
    if(_humanComponent->getWorkplace() == nullptr) //It can be that I'm unemployed and this need is the biggest one among others
        return;
    
    if(_currentTask == nullptr)
    {
        estimateTravelTiming();
        if(_minutesToHitTheRoad <= 5.0)
        {
            _dayTime->showOutputNextFrame();
            _currentTask = std::shared_ptr<HumanTask>(new WorkHumanTask());
            _humanComponent->humanAIMaster->humanTaskQueue->addTask(_currentTask);
            _canBeCancelled = false;
            LOG("Human sent to work!!!");
        }
    }
    else
    {
        if(_currentTask->getState() == HTS_DONE)
        {
            _canBeCancelled = true;
            _currentTask = nullptr;
        }
    }
}

std::string HumanAIWorkNeedComponent::getNeedName()
{
    return "Work";
}

void HumanAIWorkNeedComponent::estimateTravelTiming()
{
    GameDate currentTime = _dayTime->getCurrentGameDate();
    GameDate workBegin = _humanComponent->getWorkplace()->nextWorkBegin();
    
    Vector3 pos = _parent->getTransform().getWorldPosition();
    Vector3 building = _humanComponent->getWorkplace()->parent->getParent()->getTransform().getWorldPosition();
    
    float dist = (pos - building).norm();
    _dayTime->showOutputNextFrame();
    LOGF(F("\t\tDist: %1%") % dist);
    _minutesLeft = workBegin.time - currentTime.time;
    _minutesNeedToTravel = dist / _humanComponent->humanMotion->getSpeed();
    _minutesToHitTheRoad = _minutesLeft - _minutesNeedToTravel;
    
    _dayTime->showOutputNextFrame();
    LOGF(F("Work starts in %1% minutes") % _minutesLeft);
}

void HumanAIWorkNeedComponent::updateFulfillment()
{
    _fulfillment = 0.f;
}


void HumanAIWorkNeedComponent::updatePriority()
{
    if (_humanComponent->getWorkplace() == nullptr) {
        _priority = 0.0;
        return;
    }
    estimateTravelTiming();

//    if(timeDiff >= 0.0 && timeDiff <= 30.0)
//    {
//
//        std::cout << "Human work stats:\n";
//        std::cout << "\tMinutes needed to travel to work: " << _minutesNeedToTravel << "\n";
//        std::cout << "\tHours to start working: " << _minutesLeft / 60.0 << "\n";
//        std::cout << "\tMinutes to start working: " << _minutesLeft << "\n";
//        std::cout << "\tI have to hit the road in " << _minutesToHitTheRoad << " minutes (if it's minus I'll be so late!)\n";
//        std::cout << "\tComputed priority: " << getPriority() << "\n";
//    }

//    if(_minutesToHitTheRoad <= 0.0)
//    {
//        _humanComponent->humanMotion->setTargetPosition(building);
//    }

    _priority = (1.0 - (_minutesToHitTheRoad / 30.0)) * 100.0;
    
    
    _dayTime->showOutputNextFrame();
    LOG("Debugging shit:");
    LOGF(F("\tTravel mins %1%") % _minutesNeedToTravel);
    LOGF(F("\tMins left %1%") % _minutesLeft);
    LOGF(F("\tMins to hit the road %1%") % _minutesToHitTheRoad);
    LOGF(F("\tWork priority is: %1%") % _priority);
}
