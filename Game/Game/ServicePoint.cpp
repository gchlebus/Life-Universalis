//
// Created by Chlebus, Grzegorz on 03/05/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "ServicePoint.h"
#include "IQueue.h"
#include "IService.h"
#include "HumanInteraction.h"
#include "Workplace.h"
#include "IMachine.h"

ServicePoint::ServicePoint(IService* service, IQueue* queue, size_t numWorkplaces)
    : _service(service)
    , _queue(queue)
    , _currentProgress(0)
    , _currentInteraction(nullptr)
    , _machine(nullptr)
{
    _workplaces.resize(numWorkplaces);
    for (auto& w : _workplaces)
        w = new Workplace();
    
    _dayTime = (DayTimeEntity*) (GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME));
}

ServicePoint::~ServicePoint()
{
    delete _service;
    delete _queue;
    for (auto w : _workplaces)
        delete w;
}

void ServicePoint::setParent(IMachine* parent)
{
    _machine = parent;
}

IQueue* ServicePoint::getQueue()
{
    return _queue;
}

IService* ServicePoint::getService()
{
    return _service;
}

void ServicePoint::startUsing(const HumanInteraction* interaction, IServicePoint::Callback callback)
{
    if (_canAccept())
    {
        _callback = callback;
        _currentInteraction = interaction;
        _currentProgress = 0;
    }
    else
    {
        callback(0.f);
    }
}

float ServicePoint::getProgress(const HumanInteraction* interaction)
{
    if (_currentInteraction == interaction)
        return _currentProgress;
    return 0;
}

float ServicePoint::stopUsing(const HumanInteraction* interaction)
{
    if (_currentInteraction == interaction)
    {
        _currentInteraction = nullptr;
        return _currentProgress;
    }
    return 0;
}

PaymentAgentComponent* ServicePoint::getPaymentAgent()
{
    return _machine->getPaymentAgent();
}

Vector3 ServicePoint::getWorldPosition()
{
    return _machine->getWorldPosition();
}

Workplace::PtrVector& ServicePoint::getWorkplaces()
{
    return _workplaces;
}

void ServicePoint::update()
{
    if (!_currentInteraction)
    {
        _queue->callNext();
        return;
    }

    if (!_isEnoughWorkers())
    {
        _endServiceUsage();
    }
    else
    {
        _updateCurrentProgress();
        if (_currentProgress == 1.0)
            _endServiceUsage();
    }
}

void ServicePoint::_updateCurrentProgress()
{
    double lastDelta = _dayTime->getLastDelta().time;
    double usageTime = _service->getUsageTime(_getNumWorkers());
    _currentProgress += lastDelta / usageTime;
    boost::algorithm::clamp(_currentProgress, 0, 1);
}

void ServicePoint::_endServiceUsage()
{
    _currentInteraction = nullptr;
    _callback(_currentProgress);
}

bool ServicePoint::_canAccept()
{
    return _currentInteraction == nullptr && _isEnoughWorkers();
}

bool ServicePoint::_isEnoughWorkers()
{
    size_t numWorkers = _getNumWorkers();

    const bool enoughWorkers = numWorkers >= _service->getMinimalWorkplaceOccupation();
    return enoughWorkers;
}

size_t ServicePoint::_getNumWorkers()
{
    size_t numWorkers = 0;
    for (auto& w : _workplaces)
    {
        if (w->isWorking)
            numWorkers++;
    }
    return numWorkers;
}
