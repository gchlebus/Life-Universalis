#pragma once

#include <GameEngine.h>
#include "DayTimeEntity.h"

class DayTimeEntityMock
    : public DayTimeEntity
{
public:
    void setTime(double min);

    void setLastDelta(double min);
};


class TestGameEngine
{
public:
    TestGameEngine();

    ~TestGameEngine();

    void setTime(double min)
    {
        _dayTimeEntityMock.setTime(min);
    }

    void setLastDelta(double min)
    {
        _dayTimeEntityMock.setLastDelta(min);
    }

    GameEngine* engine;

private:
    DayTimeEntityMock _dayTimeEntityMock;
};
