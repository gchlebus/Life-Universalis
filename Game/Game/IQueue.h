#pragma once

#include "GlobalHeaders.h"

class HumanInteraction;

class IQueue
{
public:
    typedef std::function<void()> Callback;

    virtual ~IQueue() {}

    virtual bool enter(const HumanInteraction* interaction, Callback callback) = 0;

    virtual void leave(const HumanInteraction* interaction) = 0;

    virtual size_t getPosition(const HumanInteraction* interaction) = 0;

    virtual void callNext() = 0;
};
