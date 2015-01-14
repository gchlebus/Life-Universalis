#include "GameObject.h"
#include "GameObjectComponent.h"

void GameObject::start()
{
	for (size_t i = 0; i < _components.size(); ++i)
	{
		_components[i]->onStart();
	}
}

void GameObject::update()
{
	for (size_t i = 0; i < _components.size(); ++i)
	{
		_components[i]->onUpdate();
	}
}

bool GameObject::addComponent(GameObjectComponent *component)
{
	bool wasAdded = false;

	const std::string &name = component->getName();
	if (!findComponent(name))
	{
		_components.push_back(component);
		component->attachToParent(this);
		wasAdded = true;
	}

	return wasAdded;
}

GameObjectComponent* GameObject::findComponent(const std::string &componentName)
{
	return nullptr;
}
