//
//  HumanInteraction.h
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include "GlobalHeaders.h"
#include "HumanInteractionControllerComponent.h"

enum HumanInteractionState
{
    HIS_IDLE,
    HIS_EXECUTING,
    HIS_TERMINATING,
    HIS_DONE
};

class HumanInteraction
{
public:
    friend HumanInteractionControllerComponent;
    HumanInteraction();
    
    virtual std::string getInteractionName() = 0;
    void terminateGracefully();
    void terminateImmediately();
    
    
    HumanInteractionState getState();
protected:
    void execute(HumanInteractionControllerComponent *parent);
    void update();
    
    virtual void onExecute();
    virtual void onUpdate();
    virtual void onTerminateGracefully();
    virtual void onTerminateImmediately();
    
    HumanInteractionState _state;
    HumanInteractionControllerComponent *_parent;
};
