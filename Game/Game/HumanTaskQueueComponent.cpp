//
//  HumanTaskQueueComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanTaskQueueComponent.h"
#include "HumanComponentNames.h"
#include "HumanTask.h"

HumanTaskQueueComponent::HumanTaskQueueComponent() : GameObjectComponent(HC_TASK_QUEUE)
{
    
}
void HumanTaskQueueComponent::addTask(std::shared_ptr<HumanTask> task)
{
    task->_humanComponent = _humanComponent;
    _tasks.push(task);
}
std::shared_ptr<HumanTask> HumanTaskQueueComponent::getCurrentTask()
{
    if(_tasks.empty())
        return nullptr;
    return _tasks.front();
}

void HumanTaskQueueComponent::terminateAllTasks()
{
    while(_tasks.size() != 0)
    {
        std::shared_ptr<HumanTask> task = _tasks.front();
        _tasks.pop();
    }
}

void HumanTaskQueueComponent::onAttachToParent()
{
    _humanComponent = (HumanComponent*)_parent->findComponent("HumanComponent");
}

void HumanTaskQueueComponent::onUpdate()
{
    if(_tasks.empty())
        return;
    
    std::shared_ptr<HumanTask> current = _tasks.front();

    if(current->getState() == HTS_DONE)
    {
        _tasks.pop();
    }
    else if(current->getState() == HTS_EXECUTING)
    {
        
    }
    else if(current->getState() == HTS_TERMINATING)
    {
        
    }
    else if(current->getState() == HTS_IDLE)
    {
        current->execute();
    }
    current->update();
}
