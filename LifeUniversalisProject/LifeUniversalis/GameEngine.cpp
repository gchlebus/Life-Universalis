#include "GameEngine.h"
#include "Kernel.h"

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
	while(true)
	{
		double lastTick = kernel->timer->getLastDelta();
		double currentTime = kernel->timer->getCurrent();
		int timeToWait = T_uS(kernel->settings->fixedFrameTime - currentTime);
		if(kernel->settings->fixedTimestep)
		{
			if(timeToWait > 0)
			{
				std::cout << "I'm waiting...";
				boost::this_thread::sleep(boost::posix_time::microseconds(timeToWait));
			}
		}
		std::cout << "Dupa - it's a one game-tick\n\tTime needed to wait: " << timeToWait << "\n\tLastDeltaTime: " << lastTick << "\n";
		kernel->timer->tick();
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