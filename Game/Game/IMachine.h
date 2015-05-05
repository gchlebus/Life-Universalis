#pragma once

#include "GlobalHeaders.h"
#include "IServicePoint.h"

class PaymentAgentComponent;
class BuildingComponent;

class IMachine
{
public:
    typedef std::vector<IMachine*> PtrVector;

    virtual ~IMachine() {}

    virtual void setParent(BuildingComponent* parent) = 0;

    virtual PaymentAgentComponent* getPaymentAgent() = 0;

    virtual Vector3 getWorldPosition() = 0;

    virtual IServicePoint::PtrVector& getServicePoints() = 0;

    virtual Workplace::PtrVector getWorkplaces() = 0;

    virtual void update() = 0;
};