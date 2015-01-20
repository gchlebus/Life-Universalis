#pragma once
#include "GlobalHeaders.h"

class Kernel;
class Scene;

class LIFEUNIVERSALIS_EXPORT GameEngine
{
public:
	GameEngine();
	~GameEngine();

	static GameEngine* engine();

	void run();

	void tempJoin();

	Kernel* kernel;
	Scene* currentScene;

protected:
	boost::thread mainLoopThread;

	void gameLoop();
	double accumulatedDeltaTime;

	static GameEngine* globalPtr;
};