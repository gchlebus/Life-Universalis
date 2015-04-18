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

HumanTaskQueueComponent::HumanTaskQueueComponent()
    : GameObjectComponent(HC_TASK_QUEUE)
{

}

void HumanTaskQueueComponent::addTask(HumanTaskPtr task)
{
    task->_humanComponent = _humanComponent;
    _tasks.push(task);
}

HumanTaskPtr HumanTaskQueueComponent::getCurrentTask()
{
    if (_tasks.empty())
        return nullptr;
    return _tasks.front();
}

void HumanTaskQueueComponent::terminateAllTasks()
{
    while (_tasks.size() != 0)
    {
        HumanTaskPtr task = _tasks.front();
        _tasks.pop();
    }
}

void HumanTaskQueueComponent::onAttachToParent()
{
    _humanComponent = (HumanComponent*) _parent->findComponent("HumanComponent");
}

void HumanTaskQueueComponent::onUpdate()
{
    if (_tasks.empty())
        return;

    HumanTaskPtr current = _tasks.front();

    if (current->getState() == HumanTask::DONE)
    {
        _tasks.pop();
    }
    else if (current->getState() == HumanTask::EXECUTING)
    {

    }
    else if (current->getState() == HumanTask::TERMINATING)
    {

    }
    else if (current->getState() == HumanTask::IDLE)
    {
        current->execute();
    }
    current->update();
}
