#pragma once
#include "GlobalHeaders.h"

class Kernel;

class LIFEUNIVERSALIS_EXPORT GameEngine
{
public:
	GameEngine();
	~GameEngine();

	static GameEngine* engine();

	void run();

	void tempJoin();

	Kernel* kernel;
protected:
	boost::thread mainLoopThread;

	void gameLoop();

	static GameEngine* globalPtr;
};