#include "TestGameEngine.h"

void DayTimeEntityMock::setTime(double min)
{
    gameDate = GameDate(min);
}

void DayTimeEntityMock::setLastDelta(double min)
{
    delta = GameDate(min);
}


TestGameEngine::TestGameEngine()
{
    engine = GameEngine::engine();
    engine->currentEnvironment = new GameEnvironment();
    engine->currentEnvironment->addEntity(&_dayTimeEntityMock);
    engine->currentScene = new Scene();

}

TestGameEngine::~TestGameEngine()
{
    delete engine->currentScene;
    delete engine->currentEnvironment;
}
