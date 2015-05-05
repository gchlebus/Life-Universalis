//
// Created by Chlebus, Grzegorz on 01/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//
#include "Machine.h"
#include "BuildingComponent.h"
#include "IServicePoint.h"

Machine::Machine()
    : _buildingComponent(nullptr)
{

}

Machine::~Machine()
{
    for (auto sp: _servicePoints)
        delete sp;
}

void Machine::setParent(BuildingComponent* parent)
{
    _buildingComponent = parent;
}

PaymentAgentComponent* Machine::getPaymentAgent()
{
    return _buildingComponent->paymentAgent;
}

Vector3 Machine::getWorldPosition()
{
    return _buildingComponent->getParent()->getTransform().getWorldPosition();
}

IServicePoint::PtrVector& Machine::getServicePoints()
{
    return _servicePoints;
}

void Machine::update()
{
    for (auto& sp: _servicePoints)
        sp->update();
}

Workplace::PtrVector Machine::getWorkplaces()
{
    Workplace::PtrVector v;

    for (auto& sp: _servicePoints)
    {
        Workplace::PtrVector tmp = sp->getWorkplaces();
        v.insert(v.end(), tmp.begin(), tmp.end());
    }

    return v;
}

void Machine::addServicePoint(IServicePoint* servicePoint)
{
    if (_isServicePointPresent(servicePoint))
    {
        servicePoint->setParent(this);
        _servicePoints.push_back(servicePoint);
    }
}

bool Machine::_isServicePointPresent(IServicePoint* servicePoint)
{
    return find(_servicePoints.begin(), _servicePoints.end(), servicePoint) == _servicePoints.end();
}
