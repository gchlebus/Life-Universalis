//
//  UseServiceHumanTask.h
//  Game
//
//  Created by Pawel Sulik on 28/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "GlobalHeaders.h"
#include "HumanTask.h"

class IServicePoint;

class UseServiceHumanTask
    : public HumanTask
{
public:
    UseServiceHumanTask(IServicePoint& servicePoint);

    virtual std::string getTaskName() override;

protected:
    virtual void onUpdate() override;

    virtual Vector3 getTarget() override;

    virtual void humanTaskWillInteract(HumanTask* task) override;

    IServicePoint& _servicePoint;
};