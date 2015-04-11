//
//  GoToHumanTask.h
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include <GameEngine.h>
#include "HumanTask.h"

class GoToHumanTask : public HumanTask
{
public:
    GoToHumanTask(Vector3 targetPosition);
    ~GoToHumanTask();
    std::string getTaskName();
    
protected:
    
    Vector3 _targetPosition;
    
    void update();
    
    void onUpdate();
    void onExecute();
    void onTerminateGracefully();
    void onTerminateImmediately();
};
