//
//  HumanTask.h
//  Game
//
//  Created by Pawel Sulik on 27/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include <GameEngine.h>
#include "HumanComponent.h"
#include "HumanTaskObserver.h"

class HumanComponent;

class HumanTaskQueueComponent;


//This class inherits from HumanTaskObserver class to implement mechanics of specific task.
//This mechanism is semi-automatic.
class HumanTask : public HumanTaskObserver
{
public:
    enum State { IDLE, GOING, EXECUTING, TERMINATING, DONE };

    friend HumanTaskQueueComponent;
    HumanTask();
    virtual ~HumanTask();
    virtual std::string getTaskName() = 0;
    
    //This method concludes current task with all clean-ups involved
    //If you are using this method internally, don't forget to call finish() at the end of termination!
    void terminateGracefully();
    
    //This method forces task termination
    void terminateImmediately();
    
    //This method pauses the task
    void pause();
    
    //This method resumes last activities
    void resume();
    
    bool isPaused();
    
    
    State getState();
    HumanComponent *_humanComponent;
protected:
    
    bool _paused;
    
    //This method is called only once - at task start
    void execute();
    
    //This method forces human to go to the target
    void goToTarget();
    
    //This method forces human to do the appriopriate activity
    void interact();
    
    //This method is called every frame
    void update();
    
    //This method is used to do the final clean-ups.
    void finish();
    
    virtual void onUpdate() = 0;
    virtual Vector3 getTarget() = 0;
private:
    State _state;
};
