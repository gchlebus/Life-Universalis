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
#include "EnvironmentEntitiesNames.h"

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
    _dayTime = (DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME);
}

HumanInteraction::Result HumanWorkInteraction::onExecute()
{
    if(_workplace == nullptr)
        return HumanInteraction::INTERACTION_INVALID;
    
    _workBegin = _workplace->nextWorkBegin();
    _workEnd = _workplace->nextWorkEnd();
    
    GameDate currentDayTime = _dayTime->getCurrentGameDate();
    
    double timeDiff = _workBegin.time - currentDayTime.time;
    
    if(timeDiff > 15.0 && !(_workBegin.time > _workEnd.time))
        return HumanInteraction::ACCESS_DENIED;
    
    _workplace->startWork();
    return HumanInteraction::OK;
}

void HumanWorkInteraction::onUpdate()
{
    GameDate currentDayTime = _dayTime->getCurrentGameDate();
    
    if(getState() == HumanInteraction::EXECUTING)
    {
        if(currentDayTime.time >= _workEnd.time)
        {
            terminateGracefully(); //It could be terminateImmediate too.
        }
    }
    if(getState() == HumanInteraction::TERMINATING)
    {
        if(currentDayTime.time >= _workEnd.time)
        {
            _workplace->endWork();
            finish();
        }
    }
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