#pragma once

#include "GlobalHeaders.h"
#include "GameObjectComponent.h"

class GameObject;

class BuildingTestComponent : public GameObjectComponent
{
public:
	BuildingTestComponent();
	~BuildingTestComponent();

	void onStart();
	void onUpdate();
	void onAttachToParent();
	void onDetachFromParent();
	void onDelete();
};
