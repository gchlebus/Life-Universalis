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
    HTS_DONE
};

class HumanTask
{
public:
    HumanTask();
    virtual ~HumanTask();
    virtual std::string getTaskName() = 0;
    virtual void update() = 0;
    
    void execute();
    void finish();
    void forceAbort();
    
    HumanTaskState getState();
    HumanComponent *_humanComponent;
protected:
    HumanTaskState _state;
    
    virtual void onExecute();
    virtual void onFinish();
    virtual void onForceAbort();
};
