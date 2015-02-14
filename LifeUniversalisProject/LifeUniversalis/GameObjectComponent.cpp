#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(const std::string &name)
	: _name(name)
{
  
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
