//
//  HumanAINeedComponent.h
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GameEngine.h>

class HumanComponent;

class Service;

class HumanAINeedComponent : public GameObjectComponent
{
public:
    HumanAINeedComponent(const std::string &name);
    virtual ~HumanAINeedComponent();

    void onParentChangedComponents();

    // Need priority in range [0, 100].
    float getPriority();

    // Need fulfillment in range [0, 1].
    float getFulfillment();

    void updateStats();

    virtual float valueImpact(Service* product);

    virtual std::string getNeedName() = 0;

    bool canBeCancelled();

protected:
    virtual void updateFulfillment() = 0;

    virtual void updatePriority() = 0;

    float _priority;
    float _fulfillment;
    bool _canBeCancelled;
    HumanComponent* _humanComponent;
};