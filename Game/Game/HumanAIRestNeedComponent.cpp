//
// Created by Chlebus, Grzegorz on 17/03/15.
// Copyright (c) 2015 LifeUniversalis. All rights reserved.
//
#include "HumanAIRestNeedComponent.h"
#include "HumanComponent.h"
#include "MotionComponent.h"
#include "RestHumanTask.h"
#include "HumanAIMasterComponent.h"
#include "HumanTaskQueueComponent.h"

HumanAIRestNeedComponent::HumanAIRestNeedComponent()
    : HumanAINeedComponent("Rest")
{
    _fulfillment = 1.f;
    _priority = 0.f;
    _getDayTimeEntity();
}

std::string HumanAIRestNeedComponent::getNeedName()
{
    return "Rest";
}

void HumanAIRestNeedComponent::onDisabled()
{
    if (_currentTask)
    {
        _currentTask->terminateImmediately();
        _currentTask.reset();
    }
}

void HumanAIRestNeedComponent::onUpdate()
{
    if (_currentTask == nullptr)
    {
        _currentTask.reset(new RestHumanTask());
        _humanComponent->humanAIMaster->humanTaskQueue->addTask(_currentTask);
    }
    else if(_currentTask->getState() == HumanTask::EXECUTING)
    {
        double lastDeltaInHours = _dayTime->getLastDelta().time / 60;
        _fulfillment += lastDeltaInHours / (_getHumanNeedRestTime() / 6);
        _fulfillment = boost::algorithm::clamp(_fulfillment, 0.f, 1.f);
    }
}

void HumanAIRestNeedComponent::updatePriority()
{
    if (_fulfillment > 0.5f)
    {
        // linear change from 0 to 25
        _priority = 25 * 2 * (1.f - _fulfillment);
    }
    else
    {
        //linear change from 25 to 100
        _priority = 25 + 75 * 2 * (0.5f - _fulfillment);
    }
}

void HumanAIRestNeedComponent::updateFulfillment()
{
    if (_currentTask == nullptr || _currentTask->getState() != HumanTask::EXECUTING)
        _fulfillment -= _getTimeSinceLastUpdateInHours() / _getHumanNeedRestTime();
}

float HumanAIRestNeedComponent::_getTimeSinceLastUpdateInHours()
{
    double val = (_dayTime->getCurrentGameDate().time - _lastUpdateTime) / 60;
    return static_cast<float>(val);
}

void HumanAIRestNeedComponent::_getDayTimeEntity()
{
    GameEnvironmentEntity* e = GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME);
    assert(e != nullptr);
    _dayTime = static_cast<DayTimeEntity*>(e);
}

float HumanAIRestNeedComponent::_getHumanNeedRestTime()
{
    const Settings* s = GameEngine::engine()->kernel->settings;
    return s->humanNeedRestTime;
}
