#include "Kernel.h"
#include "Timer.h"

Timer *Kernel::timer = 0;

bool Kernel::init()
{
	timer = new Timer();

	return true;
}