#include "TestGameEngine.h"

TestGameEngine::TestGameEngine()
{
  engine = GameEngine::engine();
  engine->kernel->settings->fixedFrameTime = 1;
  engine->kernel->settings->timeRatio = 1000 * 60; // 1ms real time = 1 min game time
  engine->currentEnvironment = new GameEnvironment();
  engine->currentScene = new Scene();
  
}

TestGameEngine::~TestGameEngine()
{
  delete engine->currentScene;
  delete engine->currentEnvironment;
}

void TestGameEngine::run()
{
  _gameLoopThread = boost::thread(&TestGameEngine::gameLoop, this);
}

void TestGameEngine::stop()
{
  _gameLoopThread.interrupt();
  _gameLoopThread.join();
}

void TestGameEngine::gameLoop()
{
  auto entities = engine->currentEnvironment->getEntities();
  auto objects = engine->currentScene->getObjects();
  
  std::for_each(entities.begin(), entities.end(),
                [](GameEnvironmentEntity *e){ e->onStart(); });
  
  std::for_each(objects.begin(), objects.end(),
                [](GameObject *o){ o->start(); });
  
  while (!boost::this_thread::interruption_requested())
  {
    engine->kernel->timer->tick();
    std::for_each(entities.begin(), entities.end(),
                  [](GameEnvironmentEntity *e){ e->onUpdate(); });
    std::for_each(objects.begin(), objects.end(),
                  [](GameObject *o){ o->update(); });
    
    boost::this_thread::disable_interruption di;
    boost::this_thread::sleep(boost::posix_time::milliseconds(engine->kernel->settings->fixedFrameTime));
  }
  
  std::for_each(entities.begin(), entities.end(),
                [](GameEnvironmentEntity *e){ e->onStop(); });
}
