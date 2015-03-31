//
//  HumanInteractionControllerComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanInteractionControllerComponent.h"
#include "HumanInteraction.h"

HumanInteractionControllerComponent::HumanInteractionControllerComponent() : GameObjectComponent("HumanInteractionControllerComponent")
{
    _currentInteraction = nullptr;
}

HumanInteractionControllerComponent::~HumanInteractionControllerComponent()
{
    
}

void HumanInteractionControllerComponent::onUpdate()
{
    if(_currentInteraction != nullptr)
    {
        _currentInteraction->update();
    }
}


int HumanInteractionControllerComponent::executeInteraction(HumanInteraction* interaction)
{
    if(interaction == nullptr)
        return -1;
    if(_currentInteraction != nullptr)
        return 0;
    _currentInteraction = interaction;
    _currentInteraction->execute(this);
    return 1;
}

void HumanInteractionControllerComponent::stopCurrentInteraction()
{
    if(_currentInteraction != nullptr)
    {
        _currentInteraction->stop();
    }
}

void HumanInteractionControllerComponent::forceAbortCurrentInteraction()
{
    if(_currentInteraction != nullptr)
    {
        _currentInteraction->forceAbort();
    }
}

HumanInteraction* HumanInteractionControllerComponent::getCurrentInteraction()
{
    return _currentInteraction;
}
