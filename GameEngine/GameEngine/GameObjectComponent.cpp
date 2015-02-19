#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(const std::string &name)
	: _name(name)
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

const std::string& GameObjectComponent::getName() const
{
	return _name;
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