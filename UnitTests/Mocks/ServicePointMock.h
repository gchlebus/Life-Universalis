#pragma once

#include <gmock/gmock.h>
#include "UseServiceHumanInteraction.h"
#include "IQueue.h"
#include "IServicePoint.h"

using ::testing::_;
using ::testing::Invoke;

class FakeServicePoint
    : public IServicePoint
{
public:
    virtual void setParent(IMachine* machine)
    {

    }

    virtual IQueue* getQueue()
    {
        return nullptr;
    }

    virtual IService* getService()
    {
        return nullptr;
    }

    virtual void startUsing(const HumanInteraction* interaction, Callback callback)
    {
        serviceCallback = callback;
    }

    virtual float getProgress(const HumanInteraction* interaction)
    {
        return 0;
    }

    virtual float stopUsing(const HumanInteraction* interaction)
    {
        return 0;
    }

    virtual PaymentAgentComponent* getPaymentAgent()
    {
        return nullptr;
    }

    virtual Vector3 getWorldPosition()
    {
        return Vector3(0, 0, 0);
    }

    virtual Workplace::PtrVector& getWorkplaces()
    {
        return workplaces;
    }

    virtual void update()
    {

    }

    Workplace::PtrVector workplaces;
    Callback serviceCallback;
};

class ServicePointMock
    : public FakeServicePoint
{
public:
    ServicePointMock()
    {
        ON_CALL(*this, startUsing(_, _)).WillByDefault(Invoke(&fakeServicePoint, &FakeServicePoint::startUsing));
    }

    MOCK_METHOD1(setParent, void(IMachine*));

    MOCK_METHOD0(getQueue, IQueue*());

    MOCK_METHOD0(getService, IService*());

    MOCK_METHOD2(startUsing, void(
        const HumanInteraction* interaction,
        Callback callback));

    MOCK_METHOD1(getProgress, float(
        const HumanInteraction* interaction));

    MOCK_METHOD1(stopUsing, float(
        const HumanInteraction* interaction));

    MOCK_METHOD0(getPaymentAgent, PaymentAgentComponent*());

    MOCK_METHOD0(getWorldPosition, Vector3());

    MOCK_METHOD0(update, void());

    FakeServicePoint fakeServicePoint;
};