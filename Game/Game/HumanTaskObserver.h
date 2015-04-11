//
//  HumanTaskObserver.h
//  Game
//
//  Created by Pawel Sulik on 07/04/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

class HumanTask;

class HumanTaskObserver
{
public:
    friend HumanTask;
protected:
    
    virtual void humanTaskDidExecute(HumanTask* task)               {}
    
    virtual void humanTaskWillGoToTarget(HumanTask* task)           {}
    virtual void humanTaskDidReachTarget(HumanTask* task)           {}
    
    virtual void humanTaskWillInteract(HumanTask* task)             {}
    virtual void humanTaskDidInteract(HumanTask* task)              {}
    
    virtual void humanTaskDidPause(HumanTask* task)                 {}
    virtual void humanTaskDidResume(HumanTask* task)                {}
    
    virtual void humanTaskWillTerminateGracefully(HumanTask* task)  {}
    virtual void humanTaskWillTerminateImmediately(HumanTask* task) {}
    virtual void humanTaskDidTerminate(HumanTask* task)             {}
};