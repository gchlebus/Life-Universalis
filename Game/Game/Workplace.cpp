//
//  Workplace.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#include "Workplace.h"
#include "HumanComponent.h"

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