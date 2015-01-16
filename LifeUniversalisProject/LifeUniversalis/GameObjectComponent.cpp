#include "GameObjectComponent.h"

GameObjectComponent::GameObjectComponent(const std::string &name, GameObject *parent)
	: _name(name)
{
	attachToParent(parent);
}

GameObjectComponent::~GameObjectComponent()
{

}

void GameObjectComponent::attachToParent(GameObject *parent)
{
	_parent = parent;
}

void GameObjectComponent::detachFromParent()
{
	_parent = nullptr;
}

const std::string& GameObjectComponent::getName() const
{
	return _name;
}
