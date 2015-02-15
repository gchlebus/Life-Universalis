#pragma once

#include <GameEngine.h>

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
