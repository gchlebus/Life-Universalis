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

class HumanInteraction
{
public:
    friend HumanInteractionControllerComponent;

    enum State
    {
        IDLE, EXECUTING, TERMINATING, DONE
    };

    enum Result
    {
        OK, HUMAN_IS_BUSY, INTERACTION_INVALID, OUT_OF_RANGE, ACCESS_DENIED, NO_EQUIPMENT
    };

    HumanInteraction();

    virtual ~HumanInteraction();

    virtual std::string getInteractionName() = 0;

    void terminateGracefully();

    void terminateImmediately();


    State getState();

protected:
    Result execute(HumanInteractionControllerComponent* parent);

    void update();

    void finish();

    virtual void onBeforeExecute() = 0;

    virtual Result onExecute() = 0;

    virtual void onUpdate();

    virtual void onTerminateGracefully();

    virtual void onTerminateImmediately();
    
    virtual void onFinish();

    virtual Vector3 getTarget() = 0;

    virtual float getDistanceThreshold() = 0;

    HumanInteractionControllerComponent* _parent;
    HumanComponent* _humanComponent;
private:
    State _state;
};
