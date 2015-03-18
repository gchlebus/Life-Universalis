//
//  HumanAITestNeedComponent.h
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GameEngine.h>
#include "HumanAINeedComponent.h"

class HumanComponent;

class HumanAITestNeedComponent : public HumanAINeedComponent
{
public:
    HumanAITestNeedComponent();
    ~HumanAITestNeedComponent();
    
    void onStart();
    void onBeforeFirstUpdate();
    void onUpdate();
    void onAttachToParent();
    void onDetachFromParent();
    void onDelete();
    void onEnabled();
    void onDisabled();
    
    std::string getNeedName();
    
protected:
    virtual void updateFulfillment() override;

    virtual void updatePriority() override;
};