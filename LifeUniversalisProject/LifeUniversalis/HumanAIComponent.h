//
//  HumanAIComponent.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#pragma once

#include "GlobalHeaders.h"
#include "GameObjectComponent.h"

class HumanComponent;

class HumanAIComponent : public GameObjectComponent
{
public:
	HumanAIComponent();
	~HumanAIComponent(void);

	void onStart();
	void onUpdate();
	void onAttachToParent();
	void onDetachFromParent();
	void onDelete();

protected:

	HumanComponent* _human;
};

