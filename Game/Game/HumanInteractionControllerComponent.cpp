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
        if(_currentInteraction->getState() == HIS_DONE)
        {
            delete _currentInteraction;
            _currentInteraction = nullptr;
        }
    }
}

HumanInteractionResult HumanInteractionControllerComponent::executeInteraction(HumanInteraction* interaction)
{
    if(interaction == nullptr)
        return HIR_INTERACTION_INVALID;
    if(_currentInteraction != nullptr)
        return HIR_HUMAN_IS_BUSY;
    if(interaction->getState() != HIS_IDLE)
        return HIR_INTERACTION_INVALID;
    
    interaction->_humanComponent = (HumanComponent*)_parent->findComponent(HC_MAIN);
    HumanInteractionResult retVal = interaction->execute(this);
    if(retVal == HIR_OK)
        _currentInteraction = interaction;
    else
        delete interaction;
    return retVal;
}

HumanInteraction* HumanInteractionControllerComponent::getCurrentInteraction()
{
    return _currentInteraction;
}
