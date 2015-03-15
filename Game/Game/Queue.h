//
//  Queue.h
//  Game
//
//  Created by Adam Michałowski on 26/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

class Queue
{
public:
    Queue(int sizeMax);
    ~Queue();
    
    bool enter(int &index, bool aquireIndex = false);
    void leave();
    
    int getQueueSize();
    int getQueueMaxSize();
    
protected:
    int getCurrentIndex();
    int peekNextIndex();
    int getNextIndex();
    
    int _sizeMax;
    int _currentIndex;
    int _lastIndex;
private:
};
