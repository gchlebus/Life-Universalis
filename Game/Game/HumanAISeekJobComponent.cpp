//
//  HumanAISeekJobComponent.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#include "HumanAISeekJobComponent.h"
#include "HumanComponent.h"
#include "Workplace.h"
#include "BuildingManagerEntity.h"


HumanAISeekJobComponent::HumanAISeekJobComponent()
: GameObjectComponent("HumanAISeekJobComponent")
{
}

HumanAISeekJobComponent::~HumanAISeekJobComponent()
{
}

void HumanAISeekJobComponent::onStart()
{
}

void HumanAISeekJobComponent::onBeforeFirstUpdate()
{
    _human = (HumanComponent*)_parent->findComponent("HumanComponent");
}
void HumanAISeekJobComponent::onUpdate()
{
    if(_human->getWorkplace() == NULL)
    {
        BuildingManagerEntity *mgr = (BuildingManagerEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_BUILDING_MGR);
        
        std::vector<Workplace*> workplaces = mgr->getWorkplaces(true);
        std::list<std::pair<Workplace*, float>> ratings;
        
        for(auto workplace : workplaces)
        {
            float rating = workplace->salary;
            ratings.insert(ratings.end(), std::make_pair(workplace, rating));
        }
        //Sorting ratings descending
        ratings.sort([&](const std::pair<Workplace*, float> &first, const std::pair<Workplace*, float> &second) -> bool
                     {
                         return first.second >= second.second;
                     });
        
        for(auto e : ratings)
        {
            if(e.first->bewerbeMich(_human))
            {
                break;
            }
        }
    }
}

void HumanAISeekJobComponent::onAttachToParent()
{
}

void HumanAISeekJobComponent::onDetachFromParent()
{
}

void HumanAISeekJobComponent::onDelete()
{
}
void HumanAISeekJobComponent::onEnabled()
{
}
void HumanAISeekJobComponent::onDisabled()
{
}