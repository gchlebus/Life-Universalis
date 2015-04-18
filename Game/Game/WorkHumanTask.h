//
//  WorkHumanTask.h
//  Game
//
//  Created by Pawel Sulik on 08/04/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GlobalHeaders.h>
#include "HumanTask.h"

class HumanWorkInteraction;

class WorkHumanTask
    : public HumanTask
{
public:

    std::string getTaskName();

protected:
    void onUpdate();

    Vector3 getTarget();

    void humanTaskDidExecute(HumanTask* task);

    void humanTaskWillInteract(HumanTask* task);

    void humanTaskWillTerminateImmediately(HumanTask* task);

    void humanTaskDidTerminate(HumanTask* task);
};