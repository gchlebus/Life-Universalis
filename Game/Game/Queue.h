//
// Created by Chlebus, Grzegorz on 25/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once

#include "IQueue.h"

class Queue
    : public IQueue
{
public:
    typedef std::pair<const HumanInteraction*, Callback> Element;

    virtual bool enter(const HumanInteraction* interaction, Callback callback) final;

    virtual void leave(const HumanInteraction* interaction) final;

    virtual size_t getPosition(const HumanInteraction* interaction) final;

    virtual void callNext() final;

private:
    bool _isInQueue(HumanInteraction const* interaction);

    bool _isQueueFull();

    bool _canAccept(HumanInteraction const* interaction);

    std::vector<Element> _queue;
};
