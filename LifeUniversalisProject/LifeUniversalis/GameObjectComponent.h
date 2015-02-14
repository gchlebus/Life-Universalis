#pragma once
#include "GlobalHeaders.h"

class GameObject;

class LIFEUNIVERSALIS_EXPORT GameObjectComponent
{
public:
	GameObjectComponent(const std::string &name);
	virtual ~GameObjectComponent();
	
	void setParent(GameObject *parent);
	const std::string& getName() const;

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onAttachToParent() = 0;
	virtual void onDetachFromParent() = 0;
	virtual void onDelete() = 0;

protected:
	GameObject *_parent;

private:
	const std::string _name;
};
