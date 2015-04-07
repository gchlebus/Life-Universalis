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

class HumanTask;
class HumanComponent;

class HumanTaskQueueComponent : public GameObjectComponent
{
public:
    HumanTaskQueueComponent();
    
    //HumanTaskQueueComponent takes ownership over HumanTask
    //HumanTask will be deleted after completion
    void addTask(HumanTask *task);
    
    HumanTask* getCurrentTask();
    
    void terminateAllTasks();
    
    void onUpdate();
    void onAttachToParent();
    
protected:
    HumanComponent* _humanComponent;
    std::queue<HumanTask*> _tasks;
};
