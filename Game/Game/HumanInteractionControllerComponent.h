//
//  HumanInteractionControllerComponent.h
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include "GlobalHeaders.h"
#include "GameObjectComponent.h"

class HumanInteraction;

class HumanInteractionControllerComponent : public GameObjectComponent
{
public:
    HumanInteractionControllerComponent();
    ~HumanInteractionControllerComponent();
    
    int executeInteraction(HumanInteraction* interaction); // 1 - OK 0 - Busy -1 - invalid interaction
    void stopCurrentInteraction();
    void forceAbortCurrentInteraction();
    
    HumanInteraction* getCurrentInteraction();
    
    void onUpdate();
protected:
    HumanInteraction *_currentInteraction;
};
