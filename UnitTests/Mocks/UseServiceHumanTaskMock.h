#pragma once

#include "UseServiceHumanTask.h"
#include "IServicePoint.h"

class UseServiceHumanTaskMock
    : public UseServiceHumanTask
{
public:
    UseServiceHumanTaskMock(IServicePoint& servicePoint);

    void doInteract();

    void doOnUpdate();
};

UseServiceHumanTaskMock::UseServiceHumanTaskMock(IServicePoint& servicePoint)
    : UseServiceHumanTask(servicePoint)
{

}

void UseServiceHumanTaskMock::doInteract()
{
    interact();
}

void UseServiceHumanTaskMock::doOnUpdate()
{
    onUpdate();
}
