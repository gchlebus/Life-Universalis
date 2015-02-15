#include "Timer.h"


Timer::Timer()
{
	startTime = 0;
	lastDelta = 0;

	boostTimer = new boost::timer::cpu_timer;
}
Timer::~Timer()
{
	delete boostTimer;
}

void Timer::tick()
{
	lastDelta = (boostTimer->elapsed().wall / 1000000.0) - startTime;
	startTime = (boostTimer->elapsed().wall / 1000000.0);
}
double Timer::getLastDelta()
{
	return lastDelta;
}
double Timer::getCurrent()
{
	return ((boostTimer->elapsed().wall / 1000000.0) - startTime);
}
double Timer::getAbsolute()
{
	return (boostTimer->elapsed().wall / 1000000.0);
}