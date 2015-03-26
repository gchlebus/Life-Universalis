//
//  Queue.cpp
//  Game
//
//  Created by Adam Michałowski on 26/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "Queue.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))


Queue::Queue(int maxSize)
{
    _maxSize = maxSize;
}

int Queue::getSize()
{
    return (int)_humans.size();
}
int Queue::getMaxSize()
{
    return _maxSize;
}

void Queue::setUnitDuration(float duration)
{
    _duration = duration;
}
float Queue::getUnitDuration()
{
    return _duration;
}

bool Queue::enter(HumanComponent* human)
{
    if(_humans.size() >= _maxSize)
        return false;
    _humans.push_back(human);
    return false;
}
void Queue::leave(HumanComponent* human)
{
    _humans.remove(human);
}


//Queue::Queue(int sizeMax)
//{
//    _sizeMax = sizeMax;
//    _currentIndex = 0;
//    _lastIndex = 0;
//}
//
//int Queue::getCurrentIndex()
//{
//    return _currentIndex;
//}
//
//int Queue::peekNextIndex()
//{
//    return _lastIndex + 1;
//}
//
//int Queue::getNextIndex()
//{
//    return _lastIndex++;
//}
//
//int Queue::getQueueSize()
//{
//    return ABS(_lastIndex - _currentIndex) % _sizeMax;
//}
//
//int Queue::getQueueMaxSize()
//{
//    return _sizeMax;
//}
//
//bool Queue::enter(int &index, bool aquireIndex)
//{
//    if(aquireIndex)
//    {
//        index = getNextIndex();
//    }
//    
//    return _currentIndex == index;
//}
//
//void Queue::leave()
//{
//    if(_currentIndex < _lastIndex)
//    {
//        _currentIndex++;
//    }
//}
