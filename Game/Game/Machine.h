//
// Created by Chlebus, Grzegorz on 01/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//
#pragma once

#include "IMachine.h"

class IServicePoint;

class Machine
    : public IMachine
{
public:
    Machine();

    virtual ~Machine();

    virtual void setParent(BuildingComponent* parent) override;

    virtual PaymentAgentComponent* getPaymentAgent() override;

    virtual Vector3 getWorldPosition() override;

    virtual IServicePoint::PtrVector& getServicePoints() override;


    virtual Workplace::PtrVector getWorkplaces() override;

    virtual void update() override;

    // Machine takes ownership of passed service point.
    void addServicePoint(IServicePoint* servicePoint);

protected:
    bool _isServicePointPresent(IServicePoint* servicePoint);

    BuildingComponent* _buildingComponent;
    IServicePoint::PtrVector _servicePoints;
};
