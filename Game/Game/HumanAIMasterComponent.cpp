//
//  HumanAIMasterComponent.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//


#include "HumanAIMasterComponent.h"
#include "HumanAINeedComponent.h"


HumanAIMasterComponent::HumanAIMasterComponent()
  : GameObjectComponent("HumanAIMasterComponent")
{
    _currentNeed = nullptr;
}

HumanAIMasterComponent::~HumanAIMasterComponent(void)
{
}

void HumanAIMasterComponent::onStart()
{
}

void HumanAIMasterComponent::onBeforeFirstUpdate()
{
}
void HumanAIMasterComponent::onUpdate()
{
    //Search for best activity right now
    if(_currentNeed == nullptr || _currentNeed->canBeCancelled())
    {
        HumanAINeedComponent *highestNeed = nullptr;
        float highestPriority = 9999.0f;
        for(HumanAINeedComponent *need : _needs)
        {
            need->updatePriority();
            need->setEnabled(false);
            if(need->getPriority() >= highestPriority)
            {
                highestNeed = need;
                highestPriority = need->getPriority();
            }
        }
        _currentNeed = highestNeed;
        _currentNeed->setEnabled(true);
    }
}

void HumanAIMasterComponent::onAttachToParent()
{
}

void HumanAIMasterComponent::onDetachFromParent()
{
}

void HumanAIMasterComponent::onDelete()
{
}
void HumanAIMasterComponent::onEnabled()
{
}
void HumanAIMasterComponent::onDisabled()
{
}