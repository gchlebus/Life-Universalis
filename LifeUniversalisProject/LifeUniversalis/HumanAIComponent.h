#pragma once

#include "GlobalHeaders.h"
#include "GameObjectComponent.h"


class HumanAIComponent : public GameObjectComponent
{
public:
	HumanAIComponent(GameObject *parent = nullptr);
	~HumanAIComponent(void);

	void onStart();
	void onUpdate();
	void onAttachToParent();
	void onDetachFromParent();
	void onDelete();
};

