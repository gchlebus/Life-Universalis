//
//  Queue.h
//  Game
//
//  Created by Adam Michałowski on 26/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include <GameEngine.h>
#include "GlobalHeaders.h"

class HumanComponent;

//class Queue
//{
//public:
//    Queue(int sizeMax);
//    ~Queue();
//    
//    bool enter(int &index, bool aquireIndex = false);
//    void leave();
//    
//    int getQueueSize();
//    int getQueueMaxSize();
//    
//protected:
//    int getCurrentIndex();
//    int peekNextIndex();
//    int getNextIndex();
//    
//    int _sizeMax;
//    int _currentIndex;
//    int _lastIndex;
//private:
//};

class Queue
{
public:
    Queue(size_t maxSize);

    size_t getSize();

    size_t getMaxSize();
    
    void setUnitDuration(float duration);
    float getUnitDuration();
    
    bool enter(HumanComponent* human);
    void leave(HumanComponent* human);
    
protected:
    std::list<HumanComponent*> _humans;
    size_t _maxSize;
    float _duration;
};