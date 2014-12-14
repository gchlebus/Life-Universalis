#pragma once
#include "GlobalHeaders.h"
#include <boost/timer/timer.hpp>

class LIFEUNIVERSALIS_EXPORT Timer
{
public:
	Timer();
	~Timer();
	void tick();
	double getLastDelta();
	double getCurrent();
	double getAbsolute();
protected:
	double startTime;
	double lastDelta;
	boost::timer::cpu_timer *boostTimer;
};