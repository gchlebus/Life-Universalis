//
//  UseServiceHumanTask.cpp
//  Game
//
//  Created by Pawel Sulik on 28/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "UseServiceHumanTask.h"
#include "HumanInteractionControllerComponent.h"
#include "UseServiceHumanInteraction.h"
#include "HumanAIMasterComponent.h"
#include "IServicePoint.h"

UseServiceHumanTask::UseServiceHumanTask(IServicePoint& servicePoint)
    : _servicePoint(servicePoint)
{

}

std::string UseServiceHumanTask::getTaskName()
{
    return HT_USE_SERVICE;
}

void UseServiceHumanTask::onUpdate()
{
    if (getState() == EXECUTING)
    {
        UseServiceHumanInteraction* interaction =
            dynamic_cast<UseServiceHumanInteraction*>(_humanComponent->humanInteraction->getCurrentInteraction());

        if (!interaction)
            terminateImmediately();

        float delta = interaction->getServiceUsageProgressDelta();
        _humanComponent->humanAIMaster->applyService(*_servicePoint.getService(), delta);
    }
}

Vector3 UseServiceHumanTask::getTarget()
{
    return _servicePoint.getWorldPosition();
}

void UseServiceHumanTask::humanTaskWillInteract(HumanTask* task)
{
    _humanComponent->humanInteraction->executeInteraction(
        new UseServiceHumanInteraction(_servicePoint));
}
