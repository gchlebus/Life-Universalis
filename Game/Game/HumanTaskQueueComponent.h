//
//  HumanTaskQueueComponent.h
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include <GameEngine.h>
#include "GlobalHeaders.h"
#include "HumanTask.h"

class HumanComponent;

class HumanTaskQueueComponent
    : public GameObjectComponent
{
public:
    HumanTaskQueueComponent();

    void addTask(HumanTaskPtr task);

    HumanTaskPtr getCurrentTask();

    void terminateAllTasks();

    void onUpdate();

    void onAttachToParent();

protected:
    HumanComponent* _humanComponent;
    std::queue<HumanTaskPtr> _tasks;
};
