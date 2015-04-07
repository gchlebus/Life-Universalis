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
    _state = HTS_IDLE;
//    observer = nullptr;
}

HumanTask::~HumanTask()
{
    
}

HumanTaskState HumanTask::getState()
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
    if(_state == HTS_IDLE)
    {
        goToTarget();
    }
    else if(_state == HTS_GOING)
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
    _state = HTS_IDLE;
}

void HumanTask::finish()
{
    _state = HTS_DONE;
    humanTaskDidTerminate(this);
}

void HumanTask::terminateGracefully()
{
    if(_state == HTS_EXECUTING)
        humanTaskDidInteract(this);
    _state = HTS_TERMINATING;
    humanTaskWillTerminateGracefully(this);
}

void HumanTask::terminateImmediately()
{
    if(_state == HTS_EXECUTING)
        humanTaskDidInteract(this);
    humanTaskWillTerminateImmediately(this);
    finish();
}

void HumanTask::goToTarget()
{
    _humanComponent->humanMotion->setTargetPosition(goTarget(), MC_PRIORITY_TASK);
    _state = HTS_GOING;
    humanTaskWillGoToTarget(this);
}

void HumanTask::interact()
{
    _state = HTS_EXECUTING;
    humanTaskWillInteract(this);
}