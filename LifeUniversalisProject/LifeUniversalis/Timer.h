#pragma once
#include "GlobalHeaders.h"
#include <boost/timer/timer.hpp>

#define T_S(t) t*0.001
#define T_MS(t) t
#define T_uS(t) t*1000.0
#define T_NS(t) t*1000.0 * 1000.0

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