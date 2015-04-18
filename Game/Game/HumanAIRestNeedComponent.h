//
// Created by Chlebus, Grzegorz on 17/03/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//
#pragma once

#include "HumanAINeedComponent.h"
#include "HumanTask.h"

class
HumanAIRestNeedComponent
    : public HumanAINeedComponent
{
public:
    HumanAIRestNeedComponent();

    virtual void onDisabled() override;

    virtual void onUpdate() override;

    virtual std::string getNeedName() override;

protected:
    virtual void updateFulfillment() override;

    virtual void updatePriority() override;

    HumanTaskPtr _currentTask;

private:
    void _getDayTimeEntity();

    float _getTimeSinceLastUpdateInHours();

    float _getHumanNeedRestTime();

    DayTimeEntity* _dayTime;
};
