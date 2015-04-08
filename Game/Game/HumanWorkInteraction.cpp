//
//  HumanWorkInteraction.cpp
//  Game
//
//  Created by Pawel Sulik on 31/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanWorkInteraction.h"
#include "HumanIncludes.h"
#include "BuildingComponent.h"
#include "Workplace.h"

HumanWorkInteraction::HumanWorkInteraction()
{
    _workplace = nullptr;
}

std::string HumanWorkInteraction::getInteractionName()
{
    return HI_WORK;
}

void HumanWorkInteraction::onBeforeExecute()
{
    _workplace = _humanComponent->getWorkplace();
}

HumanInteractionResult HumanWorkInteraction::onExecute()
{
    if(_workplace == nullptr)
        return HIR_INTERACTION_INVALID;
    _workplace->startWork();
    return HIR_OK;
}

void HumanWorkInteraction::onUpdate()
{
    //if(work is ended)
    //terminateGracefully
    //if(terminating)
    //wait for end
}

void HumanWorkInteraction::onTerminateGracefully()
{
}

void HumanWorkInteraction::onTerminateImmediately()
{
    _workplace->endWork();
}

Vector3 HumanWorkInteraction::getTarget()
{
    if(_workplace == nullptr)
        return Vector3(0, 0, 0);
    return _workplace->parent->getParent()->getTransform().getWorldPosition();
}

float HumanWorkInteraction::getDistanceThreshold()
{
    return 2.0;
}