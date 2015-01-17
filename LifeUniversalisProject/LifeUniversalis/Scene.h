#pragma once
#include "GlobalHeaders.h"

class GameObject;

class LIFEUNIVERSALIS_EXPORT Scene
{
public:
	Scene();
	~Scene();

	//! \Adds an object to scene
	void addObject(GameObject* objectToAdd);

	//! \Removes an object from scene
	void removeObject(GameObject* objectToRemove);

	//! \returns all objects in scene
	const std::vector<GameObject*> &getObjects();

	//! \returns vector of objects with given name
	std::vector<GameObject*> findObjects(std::string namesToFind);
protected:
	std::vector<GameObject*> _gameObjects;
};