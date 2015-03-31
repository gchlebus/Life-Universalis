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
void HumanInteraction::onStop()
{
    
}
void HumanInteraction::onForceAbort()
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
void HumanInteraction::stop()
{
    _state = HIS_FINISHING;
    onStop();
}
void HumanInteraction::forceAbort()
{
    _state = HIS_DONE;
    onForceAbort();
}

HumanInteractionState HumanInteraction::getState()
{
    return _state;
}