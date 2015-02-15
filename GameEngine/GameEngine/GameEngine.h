#pragma once

#include "GlobalHeaders.h"
#include "GameEnvironment.h"
#include "GameEnvironmentEntity.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Kernel.h"
#include "Scene.h"
#include "Settings.h"
#include "Timer.h"
#include "Transform.h"

class GAMEENGINE_EXPORT GameEngine
{
public:
	GameEngine();
	~GameEngine();

	static GameEngine* engine();

	void run();

	void tempJoin();

	Kernel* kernel;
	Scene* currentScene;
	GameEnvironment* currentEnvironment;


protected:
	boost::thread mainLoopThread;

	void gameLoop();
	double accumulatedDeltaTime;

	static GameEngine* globalPtr;
};