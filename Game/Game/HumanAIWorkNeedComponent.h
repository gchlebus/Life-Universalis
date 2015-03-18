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

enum HAIWState
{
    HAIW_IDLE = 0,
    HAIW_GOING_TO_WORKPLACE = 1,
    HAIW_WAITING_FOR_WORK = 2,
    HAIW_WORKING = 3,
};

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
    void _estimateWorkingDates();
    void _estimateTravelScheduling();

//    GameDate estimateNextWorkStart();
    HAIWState _currentState;
    float _minutesLeft;
    float _minutesNeedToTravel;

    float _minutesToHitTheRoad;
    DayTimeEntity* _dayTime;
    GameDate _nextWorkStart;

    GameDate _nextWorkEnd;
};
