//
//  BuildingComponent.h
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#pragma once

#include "GlobalHeaders.h"
#include "GameObjectComponent.h"

class GameObject;
class Workplace;

class BuildingComponent : public GameObjectComponent
{
public:
    BuildingComponent();
    ~BuildingComponent();
    
    void onStart();
    void onBeforeFirstUpdate();
    void onUpdate();
    void onAttachToParent();
    void onDetachFromParent();
    void onDelete();
    void onEnabled();
    void onDisabled();
    
    std::vector<Workplace*> workplaces;
    
    
};
