//
//  HumanWorkInteraction.h
//  Game
//
//  Created by Pawel Sulik on 31/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include "GlobalHeaders.h"
#include "HumanComponentNames.h"
#include "HumanInteraction.h"

class Workplace;

class HumanWorkInteraction : public HumanInteraction
{
public:
    HumanWorkInteraction();
    std::string getInteractionName();
protected:
    
    void onBeforeExecute();
    HumanInteractionResult onExecute();
    void onUpdate();
    void onTerminateGracefully();
    void onTerminateImmediately();
    
    Vector3 getTarget();
    float getDistanceThreshold();
    Workplace *_workplace;
};
