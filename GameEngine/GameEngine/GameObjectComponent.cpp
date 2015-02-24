#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(const std::string &componentName)
	: _componentName(componentName)
{
    _firstUpdate = true;
}

GameObjectComponent::~GameObjectComponent()
{

}

void GameObjectComponent::setParent(GameObject *parent)
{
    _parent = parent;
}

const std::string& GameObjectComponent::getComponentName() const
{
	return _componentName;
}

void GameObjectComponent::setEnabled(bool enabled)
{
    if(enabled == _enabled)
        return;
    _enabled = enabled;
    if(enabled)
        onEnabled();
    else
        onDisabled();
}

bool GameObjectComponent::isEnabled()
{
    return _enabled;
}

void GameObjectComponent::update()
{
    if(_firstUpdate)
    {
        onBeforeFirstUpdate();
        _firstUpdate = false;
    }
    onUpdate();
}

void GameObjectComponent::onStart()                     {}
void GameObjectComponent::onUpdate()                    {}
void GameObjectComponent::onBeforeFirstUpdate()         {}
void GameObjectComponent::onAttachToParent()            {}
void GameObjectComponent::onDetachFromParent()          {}
void GameObjectComponent::onParentChangedComponents()   {}
void GameObjectComponent::onDelete()                    {}
void GameObjectComponent::onEnabled()                   {}
void GameObjectComponent::onDisabled()                  {}