#include "GameObject.h"
#include "GameObjectComponent.h"

GameObject::~GameObject()
{
	for (size_t i = 0; i < _components.size(); ++i)
	{
		_components[i]->onDetachFromParent();
		_components[i]->detachFromParent();
		_components[i]->onDelete();
		delete _components[i];
	}
	_components.clear();
}

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
		component->onAttachToParent();
		wasAdded = true;
	}

	return wasAdded;
}

GameObjectComponent* GameObject::findComponent(const std::string &componentName)
{
	// call the const version and then cast away the constness of the return type
	const GameObject *thisInstance = this;
	const GameObjectComponent *comp = thisInstance->findComponent(componentName);
	return const_cast<GameObjectComponent*>(comp);
}

const GameObjectComponent* GameObject::findComponent(const std::string &componentName) const
{
	GameObjectComponent *comp = nullptr;

	size_t idx = 0;
	if (_getComponentIndex(componentName, idx))
	{
		comp = _components[idx];
	}

	return comp;
}

GameObjectComponent* GameObject::removeComponent(const std::string &componentName)
{
	GameObjectComponent *comp = nullptr;

	size_t idx = 0;
	if (_getComponentIndex(componentName, idx))
	{
		comp = _components[idx];
		comp->onDetachFromParent();
		comp->detachFromParent();
		_components.erase(_components.begin() + idx);
	}

	return comp;
}

bool GameObject::deleteComponent(const std::string &componentName)
{
	bool wasDeleted = false;

	GameObjectComponent *comp = removeComponent(componentName);
	if (comp)
	{
		comp->onDelete();
		delete comp;
		wasDeleted = true;
	}

	return wasDeleted;
}

const std::string GameObject::getName()
{
	return _name;
}

void GameObject::setName(std::string newName)
{
	_name = newName;
}

bool GameObject::_getComponentIndex(const std::string &componentName, size_t &idx) const
{
	bool wasFound = false;

	for (size_t i = 0; i < _components.size(); ++i)
	{
		const GameObjectComponent *comp = _components[i];
		if (comp->getName() == componentName)
		{
			wasFound = true;
			idx = i;
			break;
		}
	}

	return wasFound;
}