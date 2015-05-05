#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServicePoint.h"
#include "ServiceMock.h"
#include "QueueMock.h"
#include "Workplace.h"
#include "HumanInteractionMock.h"
#include "TestGameEngine.h"

using ::testing::Return;
using ::testing::_;

class GivenServicePoint
    : public ::testing::Test
{
protected:
    GivenServicePoint()
    {
        serviceMock = new ServiceMock();
        queueMock = new QueueMock();
        servicePoint = new ServicePoint(serviceMock, queueMock, 3);

        ON_CALL(*serviceMock, getMinimalRequiredOccupation()).WillByDefault(Return(1));
        ON_CALL(*serviceMock, getUsageTime(1)).WillByDefault(Return(60));
        ON_CALL(*serviceMock, getUsageTime(2)).WillByDefault(Return(30));
    }

    ~GivenServicePoint()
    {
        delete servicePoint;
    }

    void setWorkplaceOccupation(size_t num)
    {
        size_t counter = 0;
        for (auto w : servicePoint->getWorkplaces())
        {
            if (counter++ < num)
                w->isWorking = true;
            else
                w->isWorking = false;
        }
    }

    ServicePoint* servicePoint;
    ServiceMock* serviceMock;
    QueueMock* queueMock;
    TestGameEngine testEngine;
};

class ServicePointCallback
{
public:
    virtual void foo(float progress) {}
};

class ServicePointCallbackMock
: public ServicePointCallback
{
public:
    MOCK_METHOD1(foo, void(float));
};

TEST_F(GivenServicePoint, WhenNotEnoughPeopleAtWork_ThenOnStartUsingCallbackImmediatelyCalled)
{
    setWorkplaceOccupation(0);
    ServicePointCallbackMock callbackMock;
    EXPECT_CALL(callbackMock, foo(0));
    servicePoint->startUsing(new HumanInteractionMock(), std::bind(&ServicePointCallbackMock::foo, &callbackMock,
        std::placeholders::_1));
}

TEST_F(GivenServicePoint, WhenEnoughPeopleAtWork_ThenOnStartUsingCallbackNotCalled)
{
    setWorkplaceOccupation(1);
    ServicePointCallbackMock callbackMock;
    EXPECT_CALL(callbackMock, foo(_)).Times(0);
    servicePoint->startUsing(new HumanInteractionMock(), std::bind(&ServicePointCallbackMock::foo, &callbackMock,
        std::placeholders::_1));
}

TEST_F(GivenServicePoint, WhenOnUpdateCalled_ThenCallNextFromQueueCalled)
{
    EXPECT_CALL(*queueMock, callNext());
    servicePoint->update();
}

class GivenServicePointWithUsingInteraction
    : public GivenServicePoint
{
protected:
    GivenServicePointWithUsingInteraction()
    {
        setWorkplaceOccupation(1);
        servicePoint->startUsing(&interactionMock, std::bind(&ServicePointCallbackMock::foo, &callbackMock,
            std::placeholders::_1));
    }

    HumanInteractionMock interactionMock;
    ServicePointCallbackMock callbackMock;
};

TEST_F(GivenServicePointWithUsingInteraction, GetProgress)
{
    testEngine.setLastDelta(30);
    servicePoint->update();
    ASSERT_DOUBLE_EQ(0.5, servicePoint->getProgress(&interactionMock));

    testEngine.setLastDelta(7.5);
    setWorkplaceOccupation(2);
    servicePoint->update();
    ASSERT_DOUBLE_EQ(0.75, servicePoint->getProgress(&interactionMock));
}

TEST_F(GivenServicePointWithUsingInteraction, WhenServiceFullyUsed_ThenCallbackCalled)
{
    testEngine.setLastDelta(60);
    EXPECT_CALL(callbackMock, foo(1.0));
    servicePoint->update();
}

TEST_F(GivenServicePointWithUsingInteraction, WhenStopUsingCalled_ThenProgressReturned)
{
    testEngine.setLastDelta(30);
    servicePoint->update();
    ASSERT_DOUBLE_EQ(0.5, servicePoint->stopUsing(&interactionMock));
}

TEST_F(GivenServicePointWithUsingInteraction,
    WhenNewInteractionStartsUsing_ThenCallbackCalledImmediately)
{
    EXPECT_CALL(callbackMock, foo(0));
    servicePoint->startUsing(new HumanInteractionMock(), std::bind(&ServicePointCallbackMock::foo, &callbackMock,
        std::placeholders::_1));
}

TEST_F(GivenServicePointWithUsingInteraction,
    WhenGetProgressCalledWithInvalidInteraction_ThenZeroReturned)
{
    testEngine.setLastDelta(30);
    servicePoint->update();
    ASSERT_DOUBLE_EQ(0.0, servicePoint->getProgress(new HumanInteractionMock()));
}

TEST_F(GivenServicePointWithUsingInteraction,
    WhenDuringUsageNotEnoughWorkers_ThenCallbackCalled)
{
    testEngine.setLastDelta(30);
    servicePoint->update();
    setWorkplaceOccupation(0);
    EXPECT_CALL(callbackMock, foo(0.5));
    servicePoint->update();
}

TEST_F(GivenServicePointWithUsingInteraction,
    WhenStopUsingCalledWithInvalidInteraction_ThenZeroReturned)
{
    testEngine.setLastDelta(30);
    servicePoint->update();
    ASSERT_DOUBLE_EQ(0.0, servicePoint->stopUsing(new HumanInteractionMock()));
}