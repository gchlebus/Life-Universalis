#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Queue.h"
#include "HumanInteractionMock.h"

#define EMPTY_CALLBACK [](){}

TEST(QueueTest, CreateInstance)
{
    Queue* queue = new Queue();
}

class GivenEmptyQueue
    : public ::testing::Test
{
protected:
    GivenEmptyQueue()
    {
        queue = new Queue();
        interactionMock = new HumanInteractionMock();
    }

    Queue* queue;
    HumanInteractionMock* interactionMock;
};

TEST_F(GivenEmptyQueue, WhenEnterCalled_ThenTrueReturned)
{
    ASSERT_TRUE(queue->enter(interactionMock, EMPTY_CALLBACK));
}

TEST_F(GivenEmptyQueue, WhenEnterCalledTwiceWithSameInteraction_ThenSecondEnterCallReturnsFalse)
{
    queue->enter(interactionMock, EMPTY_CALLBACK);
    ASSERT_FALSE(queue->enter(interactionMock, EMPTY_CALLBACK));
}

class Callback
{
public:
    virtual void foo() = 0;
};

class CallbackMock
    : public Callback
{
public:
    MOCK_METHOD0(foo, void());
};


TEST_F(GivenEmptyQueue, WhenNextPleaseCalled_CallbackCalled)
{
    HumanInteractionMock* interactionMock = new HumanInteractionMock();
    CallbackMock callbackMock;
    EXPECT_CALL(callbackMock, foo());
    queue->enter(interactionMock, std::bind(&CallbackMock::foo, &callbackMock));
    queue->callNext();
}

class GivenQueueWithInteractions
    : public GivenEmptyQueue
{
protected:
    GivenQueueWithInteractions()
    {
        interaction0 = new HumanInteractionMock();
        interaction1 = new HumanInteractionMock();
        interaction2 = new HumanInteractionMock();
        queue->enter(interaction0, EMPTY_CALLBACK);
        queue->enter(interaction1, EMPTY_CALLBACK);
        queue->enter(interaction2, EMPTY_CALLBACK);
    }

    HumanInteractionMock* interaction0;
    HumanInteractionMock* interaction1;
    HumanInteractionMock* interaction2;
};

TEST_F(GivenQueueWithInteractions,
    WhenInteractionLeavedQueue_ThenInvalidPositionReturned)
{
    queue->leave(interaction1);
    ASSERT_EQ(SIZE_T_MAX, queue->getPosition(interaction1));
}

TEST_F(GivenQueueWithInteractions, WhenCallNextCalled_ThenFirstInteractionNotInQueue)
{
    queue->callNext();
    ASSERT_EQ(SIZE_T_MAX, queue->getPosition(interaction0));
}

TEST_F(GivenQueueWithInteractions, GetPosition)
{
    ASSERT_EQ(0, queue->getPosition(interaction0));
    ASSERT_EQ(1, queue->getPosition(interaction1));
    ASSERT_EQ(2, queue->getPosition(interaction2));
    ASSERT_EQ(SIZE_T_MAX, queue->getPosition(new HumanInteractionMock()));
}
