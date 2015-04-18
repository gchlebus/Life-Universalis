//
// Created by Chlebus, Grzegorz on 18/04/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "RestHumanTask.h"
#include "HumanComponentNames.h"
#include "HumanInteractionControllerComponent.h"

std::string RestHumanTask::getTaskName()
{
    return HT_REST;
}

Vector3 RestHumanTask::getTarget()
{
    return _humanComponent->getHome()->getTransform().getWorldPosition();
}

void RestHumanTask::onUpdate()
{

}
