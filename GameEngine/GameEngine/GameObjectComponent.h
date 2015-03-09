#pragma once
#include "GlobalHeaders.h"

class GameObject;

class GAMEENGINE_EXPORT GameObjectComponent
{
public:
	GameObjectComponent(const std::string &componentName);
	virtual ~GameObjectComponent();
	
	void setParent(GameObject *parent);
    void setEnabled(bool enabled);
    void update();
    bool isEnabled();
	const std::string& getComponentName() const;

    virtual void onStart();
    virtual void onUpdate();
    virtual void onBeforeFirstUpdate();
    virtual void onAttachToParent();
    virtual void onDetachFromParent();
    virtual void onParentChangedComponents(); //It probably would be better if this method became a pointer to the new added OR removed component.
    virtual void onDelete();
    virtual void onEnabled();
    virtual void onDisabled();

protected:
	GameObject *_parent;
    bool _enabled;
    bool _firstUpdate;

private:
	const std::string _componentName;
};
