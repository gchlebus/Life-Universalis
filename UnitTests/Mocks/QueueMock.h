#pragma once

#include <gmock/gmock.h>
#include "IQueue.h"

using ::testing::_;
using ::testing::Invoke;

class FakeQueue
    : public IQueue
{
public:

    virtual bool enter(const HumanInteraction* interaction, Callback callback);

    virtual void leave(const HumanInteraction* interaction);

    virtual size_t getPosition(const HumanInteraction* interaction);

    virtual void callNext();

    Callback queueCallback;
};

class QueueMock
    : public FakeQueue
{
public:
    QueueMock();

    MOCK_METHOD2(enter, bool(const HumanInteraction*, Callback));

    MOCK_METHOD1(leave, void(const HumanInteraction*));

    MOCK_METHOD0(callNext, void());

    FakeQueue fakeQueue;
};
