#pragma once
#include "LifeUniversalisSystem.h"

#include <vector>
#include <string>

class GameObjectComponent;

class LIFEUNIVERSALIS_EXPORT GameObject
{
public:
	~GameObject();
	void start();
	void update();
	
	//! \return True if component was added, false otherwise.
	bool addComponent(GameObjectComponent *component);
    
	//! \return Pointer to found component, null if component was not found.
	GameObjectComponent* findComponent(const std::string &componentName);
	const GameObjectComponent* findComponent(const std::string &componentName) const;
	
	//! \return Pointer to removed component, null if component was not found.
	GameObjectComponent* removeComponent(const std::string &componentName);
	
	//! \return True if component was deleted, false otherwise.
	bool deleteComponent(const std::string &componentName);

private:
	//! Gets component index in internal component vector.
	//! \return True if idx is valid, false otherwise.
	bool _getComponentIndex(const std::string &componentName, size_t &idx) const;

	std::vector<GameObjectComponent*> _components;
};
