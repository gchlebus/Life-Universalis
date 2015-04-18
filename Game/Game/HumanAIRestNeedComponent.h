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

    virtual void onUpdate() override;

    virtual std::string getNeedName() override;

protected:
    virtual void updateFulfillment() override;

    virtual void updatePriority() override;

private:
    void _getDayTimeEntity();

    float _getTimeSinceLastUpdateInHours();

    float _getHumanNeedRestTime();

    std::shared_ptr<HumanTask> _currentTask;

    DayTimeEntity* _dayTime;
public:
    virtual void onDisabled() override;
};
