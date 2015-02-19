//
//  HumanAINeedComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 19/02/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "HumanAINeedComponent.h"

HumanAINeedComponent::HumanAINeedComponent(const std::string &name) : GameObjectComponent("HumanAINeed" + name)
{
}
HumanAINeedComponent::~HumanAINeedComponent()
{
}

bool HumanAINeedComponent::canBeCancelled()
{
    return _canBeCancelled;
}


float HumanAINeedComponent::getPriority()
{
    _priority = boost::algorithm::clamp(_priority, 0.0f, 100.0f);
    return _priority;
}
float HumanAINeedComponent::getProgress()
{
    _progress = boost::algorithm::clamp(_progress, 0.0f, 1.0f);
    return _progress;
}