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
    _currentState = HAIW_IDLE;
    _dayTime = (DayTimeEntity*) GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME);
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
    
    if(_currentState == HAIW_IDLE)
    {
        _estimateTravelScheduling();
        _dayTime->showOutputNextFrame();
        LOGF(F("Mam jeszcze tyle minut: %1%") % _minutesToHitTheRoad);
        if(_minutesToHitTheRoad <= 15.0f) //15 minutes for margin. It is better to wait than to be late
        {
            _canBeCancelled = false;
            _humanComponent->humanMotion->setTargetPosition(_humanComponent->getWorkplace()->parent->getParent()->getTransform().getWorldPosition());
            _currentState = HAIW_GOING_TO_WORKPLACE;
            LOGF(F("Ide do pracy! Mam jeszcze %1%") % _minutesToHitTheRoad);
            LOGF(F("Computed priority: %1%") % getPriority());
        }
    }
    else if(_currentState == HAIW_GOING_TO_WORKPLACE)
    {
        _estimateTravelScheduling();
        if(_humanComponent->humanMotion->isAtTargetPosition())
        {
            _currentState = HAIW_WAITING_FOR_WORK;
            _dayTime->showOutputNextFrame();
            LOGF(F("Czekam na prace! Zaczynam za %1%")%_minutesLeft);
            LOGF(F("Computed priority: %1%") % getPriority());
        }
    }
    else if(_currentState == HAIW_WAITING_FOR_WORK)
    {
        _estimateTravelScheduling();
        if(_minutesLeft <= 2.0)
        {
            _currentState = HAIW_WORKING;
            _humanComponent->getWorkplace()->startWork();
            _dayTime->showOutputNextFrame();
            LOG("ZACZALEM PRACE!!!");
            LOGF(F("Computed priority: %1%") % getPriority());
        }
    }
    else if(_currentState == HAIW_WORKING)
    {
        GameDate current = _dayTime->getCurrentGameDate();
        if(current >= _nextWorkEnd)
        {
            _humanComponent->getWorkplace()->endWork();
            _currentState = HAIW_IDLE;
            _canBeCancelled = true;
            _estimateWorkingDates(); //This is for determining new working dates. It has to be computed to set new priority
            _dayTime->showOutputNextFrame();
            LOG("Skonczylem prace!!!");
            LOGF(F("Computed priority: %1%") % getPriority());
        }
    }
}

std::string HumanAIWorkNeedComponent::getNeedName()
{
    return "Work";
}

void HumanAIWorkNeedComponent::_estimateWorkingDates()
{
    GameDate current = _dayTime->getCurrentGameDate();
    
    
    double workStart = _humanComponent->getWorkplace()->startHour;  //THIS IS IN HOURS!!!
    double diff = workStart - current.getDayHour();
    double nextWorkTime = current.time + diff * GD_HOUR;
    
    
    if(diff >= 0)
        _nextWorkStart = GameDate(nextWorkTime); //AND THOSE ARE IN MINUTES!!!
    else
        _nextWorkStart = GameDate(nextWorkTime + 1.0 * GD_DAY); //THOSE TOO!!!
    
    _nextWorkEnd = GameDate(_nextWorkStart.time + 8.0 * GD_HOUR);
    
}

void HumanAIWorkNeedComponent::_estimateTravelScheduling()
{
    GameDate currentTime = _dayTime->getCurrentGameDate();
    
    Vector3 pos = _parent->getTransform().getWorldPosition();
    Vector3 building = _humanComponent->getWorkplace()->parent->getParent()->getTransform().getWorldPosition();
    
    float dist = (pos - building).norm();
    _dayTime->showOutputNextFrame();
    LOGF(F("\t\tDist: %1%") % dist);
    _minutesLeft = _nextWorkStart.time - currentTime.time;
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
    _estimateWorkingDates();
    _estimateTravelScheduling();

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
