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
    _state = HIS_IDLE;
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

HumanInteractionResult HumanInteraction::execute(HumanInteractionControllerComponent *parent)
{
    HumanInteractionResult retVal = HIR_OK;
    _parent = parent;
    
    onBeforeExecute();
    
    Vector3 dist = parent->getParent()->getTransform().getWorldPosition() - getTarget();
    if(dist.norm() > getDistanceThreshold())
        return HIR_OUT_OF_RANGE;
    retVal = onExecute();
    if(retVal == HIR_OK)
        _state = HIS_EXECUTING;
    return retVal;
}
void HumanInteraction::update()
{
    onUpdate();
}
void HumanInteraction::terminateGracefully()
{
    _state = HIS_TERMINATING;
    onTerminateGracefully();
}
void HumanInteraction::terminateImmediately()
{
    _state = HIS_DONE;
    onTerminateImmediately();
}

HumanInteractionState HumanInteraction::getState()
{
    return _state;
}