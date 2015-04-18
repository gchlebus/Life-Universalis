//
//  HumanTask.cpp
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanTask.h"
#include "HumanIncludes.h"

HumanTask::HumanTask()
{
    _state = IDLE;
//    observer = nullptr;
}

HumanTask::~HumanTask()
{
    
}

HumanTask::State HumanTask::getState()
{
    return _state;
}

void HumanTask::execute()
{
    goToTarget();
    humanTaskDidExecute(this);
}

void HumanTask::update()
{
    if(_state == IDLE)
    {
        goToTarget();
    }
    else if(_state == GOING)
    {
        if(_humanComponent->humanMotion->isAtTargetPosition())
        {
            humanTaskDidReachTarget(this);
            interact();
        }
    }
    onUpdate();
}

void HumanTask::pause()
{
    if(_paused)
        return;
    _paused = true;
    humanTaskDidPause(this);
}

void HumanTask::resume()
{
    if(!_paused)
        return;
    _paused = false;
    humanTaskDidResume(this);
    _state = IDLE;
}

void HumanTask::finish()
{
    _state = DONE;
    humanTaskDidTerminate(this);
}

void HumanTask::terminateGracefully()
{
    if(_state == EXECUTING)
        humanTaskDidInteract(this);
    _state = TERMINATING;
    humanTaskWillTerminateGracefully(this);
}

void HumanTask::terminateImmediately()
{
    if(_state == EXECUTING)
        humanTaskDidInteract(this);
    humanTaskWillTerminateImmediately(this);
    finish();
}

void HumanTask::goToTarget()
{
    _humanComponent->humanMotion->setTargetPosition(getTarget(), MC_PRIORITY_TASK);
    _state = GOING;
    humanTaskWillGoToTarget(this);
}

void HumanTask::interact()
{
    _state = EXECUTING;
    humanTaskWillInteract(this);
}