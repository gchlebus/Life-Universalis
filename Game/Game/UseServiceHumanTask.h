//
//  UseServiceHumanTask.h
//  Game
//
//  Created by Pawel Sulik on 28/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "GlobalHeaders.h"
#include "HumanTask.h"

class UseServiceHumanTask : public HumanTask
{
public:
    UseServiceHumanTask();
    ~UseServiceHumanTask();
    std::string getTaskName();
    void update();
    
    
protected:
    HumanTaskState _state;
    
    void onExecute();
    void onFinish();
    void onForceAbort();
};