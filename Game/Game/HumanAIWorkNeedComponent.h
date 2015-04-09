//
//  HumanAIWorkNeedComponent.h
//  Game
//
//  Created by Pawel Sulik on 10/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GameEngine.h>
#include "HumanAINeedComponent.h"
#include "DayTimeEntity.h"


class HumanAIWorkNeedComponent : public HumanAINeedComponent
{
public:
    HumanAIWorkNeedComponent();
    
    void onUpdate();
    void onAttachToParent();

    //Just for tests
    void onEnabled();
    void onDisabled();
    
    std::string getNeedName();
    
protected:
    virtual void updateFulfillment() override;
    virtual void updatePriority() override;
    void estimateTravelTiming();

    float _minutesLeft;
    float _minutesNeedToTravel;
    float _minutesToHitTheRoad;
    
    DayTimeEntity* _dayTime;
};
