//
// Created by Chlebus, Grzegorz on 19/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include "HumanInteraction.h"

class IServicePoint;

class UseServiceHumanInteraction
    : public HumanInteraction
{
public:
    UseServiceHumanInteraction(IServicePoint& servicePoint);

    virtual std::string getInteractionName() override;

    float getServiceUsageProgressDelta();

protected:
    virtual void onTerminateImmediately() override;

    virtual void onFinish() override;

    virtual void onBeforeExecute() override;

    virtual Vector3 getTarget() override;

    virtual Result onExecute() override;

    virtual void onUpdate() override;

    virtual float getDistanceThreshold() override;

    void _payForService();

    IServicePoint& _servicePoint;
    bool _standingInQueue;
    bool _usingService;
    float _lastProgress;
    float _currentProgress;
};
