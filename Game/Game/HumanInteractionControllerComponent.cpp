//
//  HumanInteractionControllerComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanInteractionControllerComponent.h"

HumanInteractionControllerComponent::HumanInteractionControllerComponent() : GameObjectComponent(HC_INTERACTION_CONTROLLER)
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
        if(_currentInteraction->getState() == HumanInteraction::DONE)
        {
            delete _currentInteraction;
            _currentInteraction = nullptr;
        }
    }
}

HumanInteraction::Result HumanInteractionControllerComponent::executeInteraction(HumanInteraction* interaction)
{
    if(interaction == nullptr)
        return HumanInteraction::INTERACTION_INVALID;
    if(_currentInteraction != nullptr)
        return HumanInteraction::HUMAN_IS_BUSY;
    if(interaction->getState() != HumanInteraction::IDLE)
        return HumanInteraction::INTERACTION_INVALID;
    
    interaction->_humanComponent = (HumanComponent*)_parent->findComponent(HC_MAIN);
    HumanInteraction::Result retVal = interaction->execute(this);
    if(retVal == HumanInteraction::OK)
        _currentInteraction = interaction;
    else
        delete interaction;
    return retVal;
}

HumanInteraction* HumanInteractionControllerComponent::getCurrentInteraction()
{
    return _currentInteraction;
}
