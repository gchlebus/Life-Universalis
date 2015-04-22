//
//  HumanInteraction.cpp
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanInteraction.h"
#include "HumanInteractionControllerComponent.h"

HumanInteraction::HumanInteraction()
{
    _state = IDLE;
}
HumanInteraction::~HumanInteraction()
{
    
}

void HumanInteraction::onUpdate()
{
    
}
void HumanInteraction::onTerminateGracefully()
{
    
}
void HumanInteraction::onTerminateImmediately()
{
    
}
void HumanInteraction::onFinish()
{
    
}

HumanInteraction::Result HumanInteraction::execute(HumanInteractionControllerComponent *parent)
{
    Result retVal = OK;
    _parent = parent;
    
    onBeforeExecute();
    
    Vector3 dist = parent->getParent()->getTransform().getWorldPosition() - getTarget();
    if(dist.norm() > getDistanceThreshold())
        return OUT_OF_RANGE;
    retVal = onExecute();
    if(retVal == OK)
        _state = EXECUTING;
    return retVal;
}
void HumanInteraction::update()
{
    onUpdate();
}
void HumanInteraction::terminateGracefully()
{
    _state = TERMINATING;
    onTerminateGracefully();
}
void HumanInteraction::terminateImmediately()
{
    onTerminateImmediately();
    finish();
}
void HumanInteraction::finish()
{
    _state = DONE;
    onFinish();
}

HumanInteraction::State HumanInteraction::getState()
{
    return _state;
}