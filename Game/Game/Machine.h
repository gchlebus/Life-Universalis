//
// Created by Chlebus, Grzegorz on 01/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//
#pragma once


#include "Service.h"
#include "Queue.h"
#include "Workplace.h"
#include "BuildingComponent.h"

typedef std::vector<Workplace*> WorkplaceVector;

class Machine
{
public:

    Machine(size_t queueSize = 10, BuildingComponent* parent = nullptr);

    virtual ~Machine();

    const Service& getService() const;

    const Queue& getQueue() const;

    const WorkplaceVector& getWorkplaces() const;

    const BuildingComponent& getParent() const;

    // Machine takes ownership of workplace.
    void addWorkplace(Workplace* workplace);

protected:
    bool const _isWorkplacePresent(Workplace* workplace);

    Service _service;
    Queue _queue;
    WorkplaceVector _workplaces;
    BuildingComponent* _parent;
};
