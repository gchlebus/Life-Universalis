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
#include "HumanComponentNames.h"


HumanAIMasterComponent::HumanAIMasterComponent()
  : GameObjectComponent(HC_AI_MASTER)
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
        LOG("Checking needs...");
        for(HumanAINeedComponent *need : _needs)
        {
            need->updateStats();
            LOGF(F("\tNeed %1%\n\twith priority %2%") % need->getNeedName() % need->getPriority());
            LOG("Next...");
            if(need->getPriority() > highestPriority)
            {
                highestNeed = need;
                highestPriority = need->getPriority();
            }
        }
        if(highestNeed != nullptr && _currentNeed != highestNeed)
        {
            LOGF(F("Priority winner is %1% with highest priority %2%") % highestNeed->getNeedName() % highestNeed->getPriority());
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
    _human = (HumanComponent*)_parent->findComponent(HC_MAIN);
    humanTaskQueue = (HumanTaskQueueComponent*)_parent->findComponent(HC_TASK_QUEUE);
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