#pragma once

#include <GameEngine.h>

class TestGameEngine
{
public:
  TestGameEngine();
  ~TestGameEngine();
  void run();
  void stop();
  
  GameEngine *engine;
  
private:
  void gameLoop();
  
  boost::thread _gameLoopThread;
};
