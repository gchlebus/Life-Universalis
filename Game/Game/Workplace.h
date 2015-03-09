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
    Workplace();
    BuildingComponent* parent;
    HumanComponent* human;
    float salary; //cash units per hour
    float startHour;
    
    
    //There will be getter in the future.
    //KISS rule for now.
    bool isOffer;
    bool isWorking;
    
    bool bewerbeMich(HumanComponent* employee);
    
    //Only for employees!
    //It is probably better to implement an extra interface for employees only for this interaction, but it is not necessary now.
    void startWork();
    void endWork();
protected:
};