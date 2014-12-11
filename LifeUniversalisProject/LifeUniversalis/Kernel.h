#pragma once
#include "GlobalHeaders.h"

class Timer;

class Kernel
{
public:
	static bool init();
	static Timer *timer;
};