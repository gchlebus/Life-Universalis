//
//  BuildingComponent.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#include "BuildingComponent.h"
#include "Service.h"

BuildingComponent::BuildingComponent() : GameObjectComponent("BuildingComponent")
{
    service = new Service("ServiceName", this);
}
BuildingComponent::~BuildingComponent()
{
    
}

void BuildingComponent::onStart()
{
    
}
void BuildingComponent::onBeforeFirstUpdate()
{
}
void BuildingComponent::onUpdate()
{
    
}
void BuildingComponent::onAttachToParent()
{
    
}
void BuildingComponent::onDetachFromParent()
{
    
}
void BuildingComponent::onDelete()
{
    
}
void BuildingComponent::onEnabled()
{
    
}
void BuildingComponent::onDisabled()
{
    
}