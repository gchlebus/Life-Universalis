//
//  HumanInteraction.cpp
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanInteraction.h"

HumanInteraction::HumanInteraction()
{
    _state = HIS_IDLE;
}

void HumanInteraction::onExecute()
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

void HumanInteraction::execute(HumanInteractionControllerComponent *parent)
{
    _state = HIS_EXECUTING;
    _parent = parent;
    onExecute();
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