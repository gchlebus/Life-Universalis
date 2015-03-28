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

class GoToHumanTask
{
public:
    GoToHumanTask(Vector3 targetPosition);
    ~GoToHumanTask();
    std::string getTaskName();
    void update();
    
protected:
    
    Vector3 _targetPosition;
    
    void onExecute();
    void onFinish();
    void onForceAbort();
};
