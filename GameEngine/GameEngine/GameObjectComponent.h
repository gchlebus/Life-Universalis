#pragma once
#include "GlobalHeaders.h"

class GameObject;

class GAMEENGINE_EXPORT GameObjectComponent
{
public:
	GameObjectComponent(const std::string &name);
	virtual ~GameObjectComponent();
	
	void setParent(GameObject *parent);
    void setEnabled(bool enabled);
    void update();
    bool isEnabled();
	const std::string& getName() const;

    virtual void onStart();
    virtual void onUpdate();
    virtual void onBeforeFirstUpdate();
    virtual void onAttachToParent();
    virtual void onDetachFromParent();
    virtual void onParentChangedComponents();
    virtual void onDelete();
    virtual void onEnabled();
    virtual void onDisabled();

protected:
	GameObject *_parent;
    bool _enabled;
    bool _firstUpdate;

private:
	const std::string _name;
};
