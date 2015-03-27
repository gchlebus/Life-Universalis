//
//  HumanTask.h
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include <GameEngine.h>

class HumanComponent;

enum HumanTaskState
{
    HTS_IDLE,
    HTS_GOING,
    HTS_EXECUTING,
    HTS_FINISHING,
    HTS_ABORTING,
};

class HumanTask
{
public:
    virtual void onTaskUpdate() = 0;
    virtual std::string getTaskName() = 0;
    
    HumanTaskState getState();
protected:
    HumanTaskState _state;
    HumanComponent *_humanComponent;
};
