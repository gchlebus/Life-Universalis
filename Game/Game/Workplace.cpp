//
//  Workplace.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#include "Workplace.h"
#include "HumanComponent.h"
#include "EnvironmentEntitiesNames.h"

Workplace::Workplace()
{
    this->isOffer = true;
    this->salary = 0.0;
    this->startHour = 0.0;
    this->human = nullptr;
    this->parent = nullptr;
}

bool Workplace::bewerbeMich(HumanComponent* employee)
{
    human = employee;
    employee->setWorkplace(this);
    isOffer = false;
    return true;
}

void Workplace::startWork()
{
    isWorking = true;
}

void Workplace::endWork()
{
    isWorking = false;
    //human->cash += miliard
}

GameDate Workplace::nextWorkBegin()
{
    GameDate current = ((DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME))->getCurrentGameDate();
    
    double workStart = startHour;  //THIS IS IN HOURS!!!
    double diff = workStart - current.getDayHour();
    double nextWorkTime = current.time + diff * GD_HOUR;
    
    GameDate retVal;
    
    if(diff >= 0)
        retVal = GameDate(nextWorkTime); //AND THOSE ARE IN MINUTES!!!
    else
        retVal = GameDate(nextWorkTime + 1.0 * GD_DAY); //THOSE TOO!!!
    
    return retVal;
}

GameDate Workplace::nextWorkEnd()
{
    
    GameDate current = ((DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME))->getCurrentGameDate();
    
    double workEnd = startHour + 8.0;  //THIS IS IN HOURS!!!
    double diff = workEnd - current.getDayHour();
    double nextWorkTime = current.time + diff * GD_HOUR;
    
    GameDate retVal;
    
    if(diff >= 0)
        retVal = GameDate(nextWorkTime); //AND THOSE ARE IN MINUTES!!!
    else
        retVal = GameDate(nextWorkTime + 1.0 * GD_DAY); //THOSE TOO!!!
    
    return retVal;
}