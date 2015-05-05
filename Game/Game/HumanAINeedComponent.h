//
//  HumanAINeedComponent.h
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GameEngine.h>
#include "DayTimeEntity.h"

class HumanComponent;
class HumanAIMasterComponent;
class Service;

class HumanAINeedComponent : public GameObjectComponent
{
public:
    friend HumanAIMasterComponent;

    HumanAINeedComponent(const std::string &name);
    virtual ~HumanAINeedComponent();

    void onParentChangedComponents();
    // Need priority in range [0, 100].
    float getPriority();
    // Need fulfillment in range [0, 1].
    float getFulfillment();
    void updateStats();

    virtual std::string getNeedName() = 0;
    bool canBeCancelled();

protected:
    void increaseFulfillment(float value);
    virtual void updateFulfillment() = 0;
    virtual void updatePriority() = 0;

    float _priority;
    float _fulfillment;
    double _lastUpdateTime; // in game minutes
    bool _canBeCancelled;
    HumanComponent* _humanComponent;
    DayTimeEntity* _dayTime;
};