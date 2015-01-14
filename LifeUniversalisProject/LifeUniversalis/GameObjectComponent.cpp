#include "GameObjectComponent.h"

GameObjectComponent::GameObjectComponent(GameObject *parent /* = nullptr */)
{
	attachToParent(parent);
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
