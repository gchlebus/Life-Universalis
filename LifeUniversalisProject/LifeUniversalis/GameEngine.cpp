#include "GameEngine.h"
#include "Kernel.h"
#include "Scene.h"
#include "GameObject.h"

GameEngine* GameEngine::globalPtr = 0;

GameEngine* GameEngine::engine()
{
	if(GameEngine::globalPtr == 0)
	{
		GameEngine::globalPtr = new GameEngine();
	}
	return GameEngine::globalPtr;
}

GameEngine::GameEngine()
{
	kernel = new Kernel();
}

GameEngine::~GameEngine()
{
	delete kernel;
}

void GameEngine::gameLoop()
{
	kernel->timer->tick();
	accumulatedDeltaTime = 0;
	while(true)
	{
		double lastTick = kernel->timer->getLastDelta();
		accumulatedDeltaTime += lastTick - kernel->settings->fixedFrameTime;

		//It will be divided into multiple threads.
		if(currentScene != 0)
		{
			for(int i = 0; i < currentScene->getObjects().size(); i++)
			{
				currentScene->getObjects()[i]->update();
				//std::cout << "\n\tGameObject update. Index: " << i;
			}
			//std::cout << "\n\n";
		}

		double currentTime = kernel->timer->getCurrent() + accumulatedDeltaTime;
		int timeToWait = T_uS(kernel->settings->fixedFrameTime - currentTime);
		if(kernel->settings->fixedTimestep)
		{
			if(timeToWait > 0)
			{
				std::cout << "I'm waiting...";
				boost::this_thread::sleep(boost::posix_time::microseconds(timeToWait));
			}
		}
		std::cout << "Dupa - it's a one game-tick\n\tTime needed to wait: " << (double)timeToWait * 0.001 << "\n\tLastDeltaTime: " << lastTick << "\n\taccumulatedDeltaTimeDifference: " << accumulatedDeltaTime << "\n";
		kernel->timer->tick();
	}
}

void GameEngine::run()
{
	//temporary scene initailization
	//It produces memory leak!!! Just for test use!!!
	{
		currentScene = new Scene();
	
		for(int i = 0; i < 100000; i++)
			currentScene->addObject(new GameObject());
	}
	mainLoopThread = boost::thread(&GameEngine::gameLoop, this);
}

void GameEngine::tempJoin()
{
	mainLoopThread.join();
}