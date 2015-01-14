#pragma once

#include <vector>
#include <string>

class GameObjectComponent;

class GameObject
{
public:
	~GameObject();
	void start();
	void update();
	bool addComponent(GameObjectComponent *component);
	GameObjectComponent* findComponent(const std::string &componentName);
	bool deleteComponent(const std::string &componentName);

private:
	std::vector<GameObjectComponent*> _components;
};
