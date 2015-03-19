#include "GameEngine.h"
#include "Kernel.h"

#include "Scene.h"
#include "GameObject.h"

#include "GameEnvironment.h"
#include "GameEnvironmentEntity.h"



//#include "DayTimeEntity.h"
//#include "BuildingManagerEntity.h"
//#include "HumanManagerEntity.h"

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
	LOG("\n\n\n*******\nStarting game...\n*******");
	//Call start on all objects in current environment
	if(currentEnvironment != 0)
	{
		for(int i = 0; i < currentEnvironment->getEntities().size(); i++)
		{
			currentEnvironment->getEntities()[i]->onStart();
		}
	}

	//Call star on all objects in the scene
	if(currentScene != 0)
	{
		for(int i = 0; i < currentScene->getObjects().size(); i++)
		{
			currentScene->getObjects()[i]->start();
			//std::cout << "\n\tGameObject update. Index: " << i;
		}
		//std::cout << "\n\n";
	}
	LOG("Game started!\n*******");

	kernel->timer->tick();
	accumulatedDeltaTime = 0;
	while(true)
	{
		double lastTick = kernel->timer->getLastDelta();
		accumulatedDeltaTime += lastTick - kernel->settings->fixedFrameTime;

		
		//Call environment objects to update themselves
		if(currentEnvironment != 0)
		{
			for(int i = 0; i < currentEnvironment->getEntities().size(); i++)
			{
				currentEnvironment->getEntities()[i]->onUpdate();
			}
		}

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
//				std::cout << "I'm waiting...";
				boost::this_thread::sleep(boost::posix_time::microseconds(timeToWait));
			}
		}
//		std::cout << "Dupa - it's a one game-tick\n\tTime needed to wait: " << (double)timeToWait * 0.001 << "\n\tLastDeltaTime: " << lastTick << "\n\taccumulatedDeltaTimeDifference: " << accumulatedDeltaTime << "\n";
		kernel->timer->tick();
	}
	
	//Call environment objects to clean up all assets
	if(currentEnvironment != 0)
	{
		for(int i = 0; i < currentEnvironment->getEntities().size(); i++)
		{
			currentEnvironment->getEntities()[i]->onStop();
		}
	}
}

void GameEngine::run()
{
	mainLoopThread = boost::thread(&GameEngine::gameLoop, this);
}

void GameEngine::tempJoin()
{
	mainLoopThread.join();
}