#pragma once
#include "GlobalHeaders.h"

class Timer;
class Settings;

class LIFEUNIVERSALIS_EXPORT Kernel
{
public:
	Kernel();
	bool init();
	Timer *timer;
	Settings *settings;
};