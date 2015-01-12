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
		if(kernel->settings->fixedTimestep)
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(kernel->settings->fixedFrameTime * 1000.0));
			//mainLoopThread.sleep(boost::posix_time::milliseconds(kernel->settings->fixedFrameTime * 1000.0));
		}
		std::cout << "Dupa - it's a one game tick\n";
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