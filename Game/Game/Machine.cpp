//
// Created by Chlebus, Grzegorz on 01/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "Machine.h"
#include "Queue.h"
#include "BuildingComponent.h"


Machine::Machine(size_t queueSize, BuildingComponent* parent)
    : _queue(queueSize)
    , _service(nullptr)
{

}

Machine::~Machine()
{
    for (Workplace* w : _workplaces)
        delete w;
}

const Service& Machine::getService() const
{
    return _service;
}

Queue const& Machine::getQueue() const
{
    return _queue;
}

const WorkplaceVector& Machine::getWorkplaces() const
{
    return _workplaces;
}

const BuildingComponent& Machine::getParent() const
{
    return *_parent;
}

void Machine::addWorkplace(Workplace* workplace)
{
    if (!workplace)
        return;

    if (_isWorkplacePresent(workplace))
        _workplaces.push_back(workplace);
}

bool const Machine::_isWorkplacePresent(Workplace* workplace)
{
    return find(_workplaces.begin(), _workplaces.end(), workplace) == _workplaces.end();
}
