#pragma once

#include <string>

class GameObject;

class GameObjectComponent
{
public:
	GameObjectComponent(GameObject *parent = nullptr);
	
	void attachToParent(GameObject *parent);
	void detachFromParent();
	const std::string& getName() const;

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onAttachToParent() = 0;
	virtual void onDetachFromParent() = 0;
	virtual void onDelete() = 0;

protected:
	GameObject *_parent;
	const std::string _name;
};
