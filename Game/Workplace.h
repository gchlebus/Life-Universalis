//
//  Workplace.h
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#pragma once

class BuildingComponent;
class HumanComponent;

class Workplace
{
public:
    BuildingComponent* parent;
    HumanComponent* human;
    float salary; //cash units per hour
    float startHour;
protected:
};