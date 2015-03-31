//
// Created by Chlebus, Grzegorz on 17/03/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//
#pragma once

#include "HumanAINeedComponent.h"

class HumanAIRestNeedComponent
    : public HumanAINeedComponent
{
public:
    enum State
    {
        IDLE, GOING_HOME, RESTING
    };

    HumanAIRestNeedComponent();

    virtual void onEnabled() override;

    virtual void onUpdate() override;

    virtual std::string getNeedName() override;

protected:
    virtual void updateFulfillment() override;

    virtual void updatePriority() override;

private:
    void _getDayTimeEntity();

    float _getTimeSinceLastUpdateInHours();

    float _getHumanNeedRestTime();

    DayTimeEntity* _dayTime;
    State _state;
};
