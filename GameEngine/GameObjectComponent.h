#pragma once
#include "GlobalHeaders.h"

class GameObject;

class LIFEUNIVERSALIS_EXPORT GameObjectComponent
{
public:
	GameObjectComponent(const std::string &name);
	virtual ~GameObjectComponent();
	
	void setParent(GameObject *parent);
    void setEnabled(bool enabled);
    void update();
    bool isEnabled();
	const std::string& getName() const;

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
    virtual void onBeforeFirstUpdate() = 0;
	virtual void onAttachToParent() = 0;
	virtual void onDetachFromParent() = 0;
	virtual void onDelete() = 0;
    virtual void onEnabled() = 0;
    virtual void onDisabled() = 0;

protected:
	GameObject *_parent;
    bool _enabled;
    bool _firstUpdate;

private:
	const std::string _name;
};
