//
// Created by Chlebus, Grzegorz on 25/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "Queue.h"

bool Queue::enter(const HumanInteraction* interaction, IQueue::Callback callback)
{
    if (_canAccept(interaction))
    {
        _queue.push_back(std::make_pair(interaction, callback));
        return true;
    }
    return false;
}

void Queue::leave(const HumanInteraction* interaction)
{
    if (!_isInQueue(interaction))
        return;

    size_t i = 0;
    for (i; i < _queue.size(); ++i)
        if (_queue[i].first == interaction)
            break;

    _queue.erase(_queue.begin() + i);
}

void Queue::callNext()
{
    if (_queue.empty())
        return;

    Element e = _queue.front();
    _queue.erase(_queue.begin());
    e.second();
}

size_t Queue::getPosition(const HumanInteraction* interaction)
{
    for (size_t i = 0; i < _queue.size(); ++i)
        if (_queue[i].first == interaction)
            return i;
    return SIZE_T_MAX;
}

bool Queue::_canAccept(HumanInteraction const* interaction)
{
    return !_isInQueue(interaction);
}

bool Queue::_isInQueue(HumanInteraction const* interaction)
{
    for (size_t i = 0; i < _queue.size(); ++i)
        if (_queue[i].first == interaction)
            return true;
    return false;
}
