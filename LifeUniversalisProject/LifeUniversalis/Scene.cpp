#include "Scene.h"
#include "GameEngine.h"
#include "GameObject.h"

void Scene::addObject(GameObject* objectToAdd)
{
	_gameObjects.push_back(objectToAdd);
}

void Scene::removeObject(GameObject* objectToRemove)
{
	for(int i = 0; i < _gameObjects.size(); i++)
	{
		if(_gameObjects[i] == objectToRemove)
		{
			_gameObjects.erase(_gameObjects.begin() + i);
			return;
		}
	}
}

const std::vector<GameObject*> &Scene::getObjects()
{
	return _gameObjects;
}

std::vector<GameObject*> Scene::findObjects(std::string nameToFind)
{
	std::vector<GameObject*> retVal;
	for(int i = 0; i < _gameObjects.size(); i++)
	{
		if(_gameObjects[i]->getName() == nameToFind)
		{
			retVal.push_back(_gameObjects[i]);
		}
	}
	return _gameObjects;
}

std::vector<GameObject*> Scene::findObjects(std::vector<std::string> componentNamesToFind)
{
	std::vector<GameObject*> retVal;
	for(int i = 0; i < _gameObjects.size(); i++)
	{
		for(int k = 0; k < componentNamesToFind.size(); k++)
		{
			if(_gameObjects[i]->findComponent(componentNamesToFind[k]) != 0)
			{
				retVal.push_back(_gameObjects[i]);
				break;
			}
		}
	}
	return retVal;
}