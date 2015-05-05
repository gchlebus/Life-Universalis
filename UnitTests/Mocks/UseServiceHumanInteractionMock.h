#pragma once

#include "UseServiceHumanInteraction.h"

class UseServiceHumanInteractionMock
    : public UseServiceHumanInteraction
{
public:
    UseServiceHumanInteractionMock(IServicePoint& machine)
        : UseServiceHumanInteraction(machine)
    {
    }

    Result doOnExecute()
    {
        return onExecute();
    }

    void doOnUpdate()
    {
        onUpdate();
    }

    void setStandingInQueue(bool value)
    {
        _standingInQueue = value;
    }

    void setUsingService(bool value)
    {
        _usingService = value;
    }

    void setHumanComponent(HumanComponent* comp)
    {
        _humanComponent = comp;
    }

    Vector3 getTargetPublic()
    {
        return getTarget();
    }
};