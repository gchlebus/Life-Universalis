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
    HIS_FINISHING,
    HIS_DONE
};

class HumanInteraction
{
public:
    friend HumanInteractionControllerComponent;
    HumanInteraction();
    
    virtual std::string getInteractionName() = 0;
    
    virtual void onExecute();
    virtual void onUpdate();
    virtual void onStop();
    virtual void onForceAbort();
    
    HumanInteractionState getState();
protected:
    void execute(HumanInteractionControllerComponent *parent);
    void update();
    void stop();
    void forceAbort();
    
    HumanInteractionState _state;
    HumanInteractionControllerComponent *_parent;
};
