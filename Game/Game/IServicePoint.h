#pragma once

#include "GlobalHeaders.h"
#include "Workplace.h"

class IQueue;
class IService;
class IMachine;
class HumanInteraction;
class PaymentAgentComponent;

class IServicePoint
{
public:
    typedef std::function<void(float)> Callback;
    typedef std::vector<IServicePoint*> PtrVector;

    virtual ~IServicePoint() {}

    virtual void setParent(IMachine* parent) = 0;

    virtual IQueue* getQueue() = 0;

    virtual IService* getService() = 0;

    virtual void startUsing(const HumanInteraction* interaction, Callback callback) = 0;

    virtual float getProgress(const HumanInteraction* interaction) = 0;

    virtual float stopUsing(const HumanInteraction* interaction) = 0;

    virtual PaymentAgentComponent* getPaymentAgent() = 0;

    virtual Vector3 getWorldPosition() = 0;

    virtual Workplace::PtrVector& getWorkplaces() = 0;

    virtual void update() = 0;
};
