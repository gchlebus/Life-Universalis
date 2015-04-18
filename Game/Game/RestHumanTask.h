//
// Created by Chlebus, Grzegorz on 18/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//


#pragma once

#include "HumanTask.h"

class RestHumanTask
    : public HumanTask
{
public:
    virtual std::string getTaskName() override;

protected:

    virtual Vector3 getTarget() override;

    virtual void onUpdate() override;
};
