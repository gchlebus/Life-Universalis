//
//  HumanInteractionControllerComponent.h
//  Game
//
//  Created by Pawel Sulik on 30/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include <GameEngine.h>
#include "GlobalHeaders.h"
#include "HumanComponentNames.h"
#include "HumanInteraction.h"


class HumanInteractionControllerComponent : public GameObjectComponent
{
public:
    HumanInteractionControllerComponent();
    ~HumanInteractionControllerComponent();
    
    HumanInteractionResult executeInteraction(HumanInteraction* interaction);
    
    HumanInteraction* getCurrentInteraction();
    
    void onUpdate();
protected:
    HumanInteraction *_currentInteraction;
};
