#include "Scene.h"
#include "GameEngine.h"


void Scene::addObject(GameObject* objectToAdd)
{
	_gameObjects.push_back(objectToAdd);
}

void Scene::removeObject(GameObject* objectToRemove)
{
	//_gameObject.find(
}

const std::vector<GameObject*> &Scene::getObjects()
{
	std::vector<GameObject*> retVal;
	return retVal;
}

std::vector<GameObject*> Scene::findObjects(std::string namesToFind)
{
	return _gameObjects;
}