//
// Created by Chlebus, Grzegorz on 03/05/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include "IServicePoint.h"

class DayTimeEntity;
class HumanInteraction;

class ServicePoint
    : public IServicePoint
{
public:
    ServicePoint(IService* service, IQueue* queue, size_t numWorkplaces);

    virtual ~ServicePoint();

    virtual void setParent(IMachine* parent) override;

    virtual IQueue* getQueue() override;

    virtual IService* getService() override;

    virtual void startUsing(const HumanInteraction* interaction, Callback callback) override;

    virtual float getProgress(const HumanInteraction* interaction) override;

    virtual float stopUsing(const HumanInteraction* interaction) override;

    virtual PaymentAgentComponent* getPaymentAgent() override;

    virtual Vector3 getWorldPosition() override;

    virtual Workplace::PtrVector& getWorkplaces() override;

    virtual void update() override;

protected:
    size_t _getNumWorkers();

    bool _isEnoughWorkers();

    IMachine* _machine;
    IService* _service;
    IQueue* _queue;
    Workplace::PtrVector _workplaces;
    DayTimeEntity* _dayTime;
    const HumanInteraction* _currentInteraction;
    double _currentProgress;
    Callback _callback;

    bool _canAccept();

    void _endServiceUsage();

    void _updateCurrentProgress();
};
