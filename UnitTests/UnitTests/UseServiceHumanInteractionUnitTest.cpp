#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServicePointMock.h"
#include "UseServiceHumanInteractionMock.h"
#include "../TestGameEngine.h"
#include "HumanComponent.h"
#include "QueueMock.h"
#include "ServiceMock.h"
#include "PaymentAgentComponent.h"

using ::testing::Return;
using ::testing::Invoke;
using ::testing::_;

class GivenUseServiceInteraction
    : public ::testing::Test
{
protected:
    GivenUseServiceInteraction()
        : humanComponent("Mietek", 40)
    {
        queueMock = new QueueMock();
        serviceMock = new ServiceMock();
        servicePointMock = new ServicePointMock();
        interaction = new UseServiceHumanInteractionMock(*servicePointMock);
        humanComponent.paymentAgent = &paymentAgentComponent;
        interaction->setHumanComponent(&humanComponent);

        ON_CALL(*servicePointMock, getQueue()).WillByDefault(Return(queueMock));
        ON_CALL(*servicePointMock, getService()).WillByDefault(Return(serviceMock));
    }

    ~GivenUseServiceInteraction()
    {
        delete interaction;
        delete servicePointMock;
        delete queueMock;
        delete serviceMock;
    }

    QueueMock* queueMock;
    ServiceMock* serviceMock;
    ServicePointMock* servicePointMock;
    UseServiceHumanInteractionMock* interaction;
    TestGameEngine engine;
    HumanComponent humanComponent;
    PaymentAgentComponent paymentAgentComponent;
};

TEST_F(GivenUseServiceInteraction, GetInteractionName)
{
    ASSERT_EQ("UseServiceInteraction", interaction->getInteractionName());
}

TEST_F(GivenUseServiceInteraction, WhenOnExecuteCalled_ThenEnterQueueCalled)
{
    EXPECT_CALL(*queueMock, enter(interaction, _));
    interaction->doOnExecute();
}

TEST_F(GivenUseServiceInteraction, GetTarget)
{
    EXPECT_CALL(*servicePointMock, getWorldPosition()).WillOnce(Return(Vector3(1, 2, 3)));
    Vector3 pos = interaction->getTargetPublic();
    ASSERT_FLOAT_EQ(1, pos[0]);
    ASSERT_FLOAT_EQ(2, pos[1]);
    ASSERT_FLOAT_EQ(3, pos[2]);
}

TEST_F(GivenUseServiceInteraction,
    WhenEnterQueueReturnsFalse_ThenOnExecuteReturnsAccessDenied)
{
    ON_CALL(*queueMock, enter(_, _)).WillByDefault(Return(false));
    ASSERT_EQ(HumanInteraction::ACCESS_DENIED, interaction->doOnExecute());
}

TEST_F(GivenUseServiceInteraction, WhenEnterQueueReturnsTrue_ThenOnExecuteReturnsOK)
{
    ON_CALL(*queueMock, enter(_, _)).WillByDefault(Return(true));
    ASSERT_EQ(HumanInteraction::OK, interaction->doOnExecute());
}

TEST_F(GivenUseServiceInteraction,
    WhenNotStandingInQueueAndTerminateImmediatelyCalled_ThenLeaveQueueNotCalled)
{
    interaction->setStandingInQueue(false);
    EXPECT_CALL(*queueMock, leave(interaction)).Times(0);
    interaction->terminateImmediately();
}

TEST_F(GivenUseServiceInteraction,
    WhenStandingInQueueAndTerminateImmediatelyCalled_ThenLeaveQueueCalled)
{
    interaction->setStandingInQueue(true);
    EXPECT_CALL(*queueMock, leave(interaction));
    interaction->terminateImmediately();
}

TEST_F(GivenUseServiceInteraction,
    WhenQueueCallbackCalled_ThenStartUsingServiceCalled)
{
    interaction->doOnExecute();
    EXPECT_CALL(*servicePointMock, startUsing(interaction, _));
    queueMock->fakeQueue.queueCallback();
}

TEST_F(GivenUseServiceInteraction,
    WhenUsingServiceAndTerminateImmediatelyCalled_ThenStopUsingServiceCalled)
{
    interaction->setUsingService(true);
    EXPECT_CALL(*servicePointMock, stopUsing(interaction));
    interaction->terminateImmediately();
}

TEST_F(GivenUseServiceInteraction,
    WhenUsingServiceAndAfterOneOnUpdate_GetProgressReturnsCorrectly)
{
    interaction->setUsingService(true);
    EXPECT_CALL(*servicePointMock, getProgress(interaction)).WillOnce(Return(0.2f)).WillOnce(Return(0.6f));
    interaction->doOnUpdate();
    ASSERT_FLOAT_EQ(0.2, interaction->getServiceUsageProgressDelta());
    ASSERT_FLOAT_EQ(0, interaction->getServiceUsageProgressDelta());

    interaction->doOnUpdate();
    ASSERT_FLOAT_EQ(0.4, interaction->getServiceUsageProgressDelta());
}

TEST_F(GivenUseServiceInteraction,
    WhenUsingServiceAndAfterTwoOnUpdate_GetProgressReturnsCorrectly)
{
    interaction->setUsingService(true);
    EXPECT_CALL(*servicePointMock, getProgress(interaction)).WillOnce(Return(0.2f)).WillOnce(Return(0.6f));
    interaction->doOnUpdate();
    interaction->doOnUpdate();
    ASSERT_FLOAT_EQ(0.6, interaction->getServiceUsageProgressDelta());
}

TEST_F(GivenUseServiceInteraction,
    WhenUsingServiceTerminatesWithProgressGreaterThenZero_ThenPaymentIsDone)
{
    interaction->setUsingService(true);
    ON_CALL(*servicePointMock, stopUsing(_)).WillByDefault(Return(1));
    EXPECT_CALL(*servicePointMock, getPaymentAgent());
    interaction->terminateImmediately();
}

TEST_F(GivenUseServiceInteraction,
    WhenUsingServiceTerminatesWithProgressZero_ThenPaymentNotDone)
{
    interaction->setUsingService(true);
    ON_CALL(*servicePointMock, stopUsing(_)).WillByDefault(Return(0));
    EXPECT_CALL(*servicePointMock, getPaymentAgent()).Times(0);
    interaction->terminateImmediately();
}

TEST_F(GivenUseServiceInteraction,
    WhenServiceCallbackCalledWithProgressGreaterThanZero_ThenPaymentIsDone)
{
    interaction->doOnExecute();
    queueMock->fakeQueue.queueCallback();
    EXPECT_CALL(*servicePointMock, getPaymentAgent());
    servicePointMock->fakeServicePoint.serviceCallback(1);
}
