//
//  HumanInteraction.h
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include "GlobalHeaders.h"
//#include "HumanInteractionControllerComponent.h"

class HumanInteractionControllerComponent;
class HumanComponent;

enum HumanInteractionState
{
    HIS_IDLE,
    HIS_EXECUTING,
    HIS_TERMINATING,
    HIS_DONE
};

enum HumanInteractionResult
{
    HIR_OK,
    HIR_HUMAN_IS_BUSY,
    HIR_INTERACTION_INVALID,
    HIR_OUT_OF_RANGE,
    HIR_ACCESS_DENIED,
    HIR_NO_EQUIPMENT
};

class HumanInteraction
{
public:
    friend HumanInteractionControllerComponent;
    HumanInteraction();
    virtual ~HumanInteraction();
    
    virtual std::string getInteractionName() = 0;
    void terminateGracefully();
    void terminateImmediately();
    
    
    HumanInteractionState getState();
protected:
    HumanInteractionResult execute(HumanInteractionControllerComponent *parent);
    void update();
    void finish();
    
    virtual void onBeforeExecute() = 0;
    virtual HumanInteractionResult onExecute() = 0;
    virtual void onUpdate();
    virtual void onTerminateGracefully();
    virtual void onTerminateImmediately();
    
    virtual Vector3 getTarget() = 0;
    virtual float getDistanceThreshold() = 0;
    
    HumanInteractionControllerComponent *_parent;
    HumanComponent *_humanComponent;
private:
    HumanInteractionState _state;
};
