//
// Created by Chlebus, Grzegorz on 19/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "UseServiceHumanInteraction.h"
#include "HumanComponentNames.h"
#include "IServicePoint.h"
#include "IService.h"
#include "PaymentAgentComponent.h"
#include "IQueue.h"
#include "HumanComponent.h"

UseServiceHumanInteraction::UseServiceHumanInteraction(IServicePoint& servicePoint)
    : _servicePoint(servicePoint)
    , _standingInQueue(false)
    , _usingService(false)
    , _lastProgress(0)
    , _currentProgress(0)
{

}

std::string UseServiceHumanInteraction::getInteractionName()
{
    return HI_USE_SERVICE;
}

float UseServiceHumanInteraction::getServiceUsageProgressDelta()
{
    float delta = 0;

    if (std::abs(_currentProgress - _lastProgress) > 0.001)
    {
        delta = _currentProgress - _lastProgress;
        _lastProgress = _currentProgress;
    }

    return delta;
}

void UseServiceHumanInteraction::onBeforeExecute()
{

}

void UseServiceHumanInteraction::onFinish()
{
    if (_currentProgress > 0)
        _payForService();
}

void UseServiceHumanInteraction::onTerminateImmediately()
{
    if (_standingInQueue)
    {
        _servicePoint.getQueue()->leave(this);
        _standingInQueue = false;
    }
    if (_usingService)
    {
        _currentProgress = _servicePoint.stopUsing(this);
        _usingService = false;
    }
}

void UseServiceHumanInteraction::_payForService()
{
    unsigned int price = _currentProgress * _servicePoint.getService()->getPrice();
    _humanComponent->paymentAgent->bookPayment(price, _servicePoint.getPaymentAgent(),
            "Payment for " + _servicePoint.getService()->getName());
}

HumanInteraction::Result UseServiceHumanInteraction::onExecute()
{
    if (_servicePoint.getQueue()->enter(this, [this]()
    {
        _standingInQueue = false;
        _usingService = true;
        _servicePoint.startUsing(this, [this](float progress)
        {
            _currentProgress = progress;
            _usingService = false;
            terminateImmediately();
        });
    }))
    {
        _standingInQueue = true;
        return OK;
    }
    return ACCESS_DENIED;
}

Vector3 UseServiceHumanInteraction::getTarget()
{
    return _servicePoint.getWorldPosition();
}

float UseServiceHumanInteraction::getDistanceThreshold()
{
    return 1;
}

void UseServiceHumanInteraction::onUpdate()
{
    if (_usingService)
        _currentProgress = _servicePoint.getProgress(this);
}
