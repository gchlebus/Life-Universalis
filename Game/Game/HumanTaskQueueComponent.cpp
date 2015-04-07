//
//  HumanTaskQueueComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanTaskQueueComponent.h"
#include "HumanTask.h"

HumanTaskQueueComponent::HumanTaskQueueComponent() : GameObjectComponent("HumanTaskQueueComponent")
{
    
}
void HumanTaskQueueComponent::addTask(HumanTask *task)
{
    task->_humanComponent = _humanComponent;
    _tasks.push(task);
}
HumanTask* HumanTaskQueueComponent::getCurrentTask()
{
    return _tasks.front();
}

void HumanTaskQueueComponent::terminateAllTasks()
{
    while(_tasks.size() != 0)
    {
        HumanTask* task = _tasks.front();
        _tasks.pop();
        delete task;
    }
}

void HumanTaskQueueComponent::onAttachToParent()
{
    _humanComponent = (HumanComponent*)_parent->findComponent("HumanComponent");
}

void HumanTaskQueueComponent::onUpdate()
{
    HumanTask *current = _tasks.front();
    
    if(current == nullptr)
        return;
    current->update();
    if(current->getState() == HTS_DONE)
    {
        _tasks.pop();
        delete current;
    }
    else if(current->getState() == HTS_EXECUTING)
    {
        
    }
    else if(current->getState() == HTS_TERMINATING)
    {
        
    }
    else if(current->getState() == HTS_IDLE)
    {
        
    }
}
