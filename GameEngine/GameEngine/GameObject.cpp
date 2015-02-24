#include "GameObject.h"
#include "GameObjectComponent.h"

GameObject::~GameObject()
{
	for (size_t i = 0; i < _components.size(); ++i)
	{
		_components[i]->onDetachFromParent();
		_components[i]->setParent(nullptr);
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
        
		_components[i]->update();
	}
}

bool GameObject::addComponent(GameObjectComponent *component)
{
	bool wasAdded = false;

	const std::string &name = component->getComponentName();
	if (!findComponent(name))
	{
		_components.push_back(component);
		component->setParent(this);
		component->onAttachToParent();
        wasAdded = true;
        
        for(GameObjectComponent* comp : _components)
            comp->onParentChangedComponents();
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

std::vector<const GameObjectComponent*> GameObject::findComponentsContainingString(const std::string &componentName) const
{
    std::vector<const GameObjectComponent*> retVal;
    
    for(GameObjectComponent* comp : _components)
    {
        if(comp->getComponentName().find(componentName) != std::string::npos)
            retVal.push_back(comp);
    }
    return retVal;
}
std::vector<GameObjectComponent*> GameObject::findComponentsContainingString(const std::string &componentName)
{
    std::vector<GameObjectComponent*> retVal;
    std::vector<const GameObjectComponent*> temp;
    
    const GameObject *thisInstance = this;
    temp = thisInstance->findComponentsContainingString(componentName);
    for(const GameObjectComponent *comp : temp)
    {
        retVal.push_back(const_cast<GameObjectComponent*>(comp));
    }
    return retVal;
}

GameObjectComponent* GameObject::removeComponent(const std::string &componentName)
{
	GameObjectComponent *comp = nullptr;

	size_t idx = 0;
	if (_getComponentIndex(componentName, idx))
	{
		comp = _components[idx];
		comp->onDetachFromParent();
        comp->setParent(nullptr);
		_components.erase(_components.begin() + idx);
        
        for(GameObjectComponent* comp : _components)
            comp->onParentChangedComponents();
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

Transform& GameObject::getTransform()
{
  return _transform;
}

const Transform& GameObject::getTransform() const
{
  return _transform;
}

bool GameObject::_getComponentIndex(const std::string &componentName, size_t &idx) const
{
	bool wasFound = false;

	for (size_t i = 0; i < _components.size(); ++i)
	{
		const GameObjectComponent *comp = _components[i];
		if (comp->getComponentName() == componentName)
		{
			wasFound = true;
			idx = i;
			break;
		}
	}

	return wasFound;
}
