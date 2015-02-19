//
//  HumanAIComponent.cpp
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#pragma once

#include <GameEngine.h>

class HumanComponent;
class HumanAINeedComponent;
class HumanAISeekJobComponent;

class HumanAIMasterComponent : public GameObjectComponent
{
public:
	HumanAIMasterComponent();
	~HumanAIMasterComponent(void);

    void onStart();
    void onBeforeFirstUpdate();
    void onUpdate();
	void onAttachToParent();
	void onDetachFromParent();
    void onDelete();
    void onEnabled();
    void onDisabled();

    void addNeed(HumanAINeedComponent* need);
protected:

	HumanComponent* _human;
    
    std::vector<HumanAINeedComponent*> _needs;
    HumanAINeedComponent* _currentNeed;
};

