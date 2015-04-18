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
    
    void addTask(std::shared_ptr<HumanTask> task);
    
    std::shared_ptr<HumanTask> getCurrentTask();
    
    void terminateAllTasks();
    
    void onUpdate();
    void onAttachToParent();
    
protected:
    HumanComponent* _humanComponent;
    std::queue<std::shared_ptr<HumanTask>> _tasks;
};
