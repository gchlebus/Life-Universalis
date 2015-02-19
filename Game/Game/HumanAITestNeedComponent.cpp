//
//  HumanAITestNeedComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanAITestNeedComponent.h"


HumanAITestNeedComponent::HumanAITestNeedComponent()
: HumanAINeedComponent("HumanAITestNeedComponent")
{
}

HumanAITestNeedComponent::~HumanAITestNeedComponent()
{
}

void HumanAITestNeedComponent::onStart()
{
}

void HumanAITestNeedComponent::onBeforeFirstUpdate()
{
}
void HumanAITestNeedComponent::onUpdate()
{
}

void HumanAITestNeedComponent::onAttachToParent()
{
}

void HumanAITestNeedComponent::onDetachFromParent()
{
}

void HumanAITestNeedComponent::onDelete()
{
}
void HumanAITestNeedComponent::onEnabled()
{
}
void HumanAITestNeedComponent::onDisabled()
{
}

void HumanAITestNeedComponent::updatePriority()
{
    _priority = 50.0f;
    _progress = 0.5f;
}