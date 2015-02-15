#pragma once
#include "GlobalHeaders.h"
#include "Timer.h"
#include "Settings.h"

class LIFEUNIVERSALIS_EXPORT Kernel
{
public:
	Kernel();
	bool init();
	Timer *timer;
	Settings *settings;
};