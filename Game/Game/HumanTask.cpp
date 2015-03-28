//
//  HumanTask.cpp
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanTask.h"

HumanTask::HumanTask()
{
    _state = HTS_IDLE;
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
    _state = HTS_EXECUTING;
    this->onExecute();
}

void HumanTask::finish()
{
    _state = HTS_FINISHING;
    this->onFinish();
}

void HumanTask::forceAbort()
{
    _state = HTS_DONE;
    this->onForceAbort();
}

void HumanTask::onForceAbort()
{
    
}

void HumanTask::onFinish()
{
    
}

void HumanTask::onExecute()
{
    
}