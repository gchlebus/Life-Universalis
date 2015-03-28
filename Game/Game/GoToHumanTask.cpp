//
//  GoToHumanTask.cpp
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "GoToHumanTask.h"
#include "HumanIncludes.h"


GoToHumanTask::GoToHumanTask(Vector3 targetPosition)
{
    _targetPosition = targetPosition;
}
GoToHumanTask::~GoToHumanTask()
{
    
}
std::string GoToHumanTask::getTaskName()
{
    return "GoTo";
}
void GoToHumanTask::update()
{
    
}


void GoToHumanTask::onExecute()
{
    
}
void GoToHumanTask::onFinish()
{
    
}
void GoToHumanTask::onForceAbort()
{
    
}