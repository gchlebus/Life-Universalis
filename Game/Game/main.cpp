#include "DayTimeEntity.h"
#include "HumanManagerEntity.h"
#include "BuildingManagerEntity.h"

#include <GameEngine.h>

int main()
{
  GameEngine *e = GameEngine::engine();
  
	//temporary scene initailization
	//It produces memory leak!!! Just for test use!!!
  e->currentEnvironment = new GameEnvironment();
  e->currentEnvironment->addEntity(new DayTimeEntity());
  e->currentEnvironment->addEntity(new HumanManagerEntity());
  e->currentEnvironment->addEntity(new BuildingManagerEntity());
  
  e->currentScene = new Scene();
  for (int i = 0; i < 100000; ++i)
  {
    e->currentScene->addObject(new GameObject());
  }
  
  e->run();
  e->tempJoin();
  
	return 0;
}