//
//  HumanAITestNeedComponent.h
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GameEngine.h>
#include "HumanAINeedComponent.h"

enum HAITState
{
    HAIT_IDLE,
    HAIT_GOING,
    HAIT_WAITING_IN_QUEUE,
    HAIT_CONSUMING,
};

class HumanComponent;
class Service;
class BuildingManagerEntity;

class HumanAITestNeedComponent : public HumanAINeedComponent
{
public:
    HumanAITestNeedComponent();
    ~HumanAITestNeedComponent();
    
    void onUpdate();
    void onEnabled();
    void onDisabled();
    
    std::string getNeedName();
    
protected:
    void computeBestService();
    virtual void updateFulfillment() override;

    virtual void updatePriority() override;
    
    HAITState state;
    Service* bestService;
    int myQueueIndex;
    
    BuildingManagerEntity* buildingManager;
};