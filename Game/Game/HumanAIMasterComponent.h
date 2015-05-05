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
class HumanTaskQueueComponent;
class IService;

class
HumanAIMasterComponent : public GameObjectComponent
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
    void onParentChangedComponents();

    void applyService(IService& service, float delta);
    float rateService(IService& service, HumanAINeedComponent* need);
    
    HumanTaskQueueComponent *humanTaskQueue;
    
protected:

	HumanComponent* _human;
    
    std::vector<HumanAINeedComponent*> _needs;
    HumanAINeedComponent* _currentNeed;
    HumanAISeekJobComponent* _seekJob;
};

