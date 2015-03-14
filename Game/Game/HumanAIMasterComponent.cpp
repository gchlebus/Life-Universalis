//
//  HumanAIMasterComponent.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//


#include "HumanAIMasterComponent.h"
#include "HumanAINeedComponent.h"
#include "HumanAISeekJobComponent.h"
#include "HumanComponent.h"


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
    //If unemployed seek for new job
    _seekJob->setEnabled(_human->getWorkplace() == nullptr);
    
    //Search for best activity right now
    if(_currentNeed == nullptr || _currentNeed->canBeCancelled())
    {
        HumanAINeedComponent *highestNeed = nullptr;
        float highestPriority = 0.0f;
        for(HumanAINeedComponent *need : _needs)
        {
            need->updatePriority();
            if(need->getPriority() > highestPriority)
            {
                highestNeed = need;
                highestPriority = need->getPriority();
            }
        }
        if(highestNeed != nullptr && _currentNeed != highestNeed)
        {
            if(_currentNeed)
            _currentNeed->setEnabled(false);
            _currentNeed = highestNeed;
            _currentNeed->setEnabled(true);
        }
    }
}
void HumanAIMasterComponent::onParentChangedComponents()
{
    _needs.clear();
    std::vector<GameObjectComponent*> temp = _parent->findComponentsContainingString("HumanAINeed");
    _needs.reserve(temp.size());
    
    for(GameObjectComponent *comp : temp)
    {
        HumanAINeedComponent *need = (HumanAINeedComponent*)comp;
        if(need != _currentNeed)
            need->setEnabled(false);
        _needs.push_back(need);
    }
    _seekJob = (HumanAISeekJobComponent*)_parent->findComponent("HumanAISeekJobComponent");
    _human = (HumanComponent*)_parent->findComponent("HumanComponent");
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