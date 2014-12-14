#include "Kernel.h"
#include "Timer.h"
#include "Settings.h"

//Timer *Kernel::timer		= 0;
//Settings *Kernel::settings	= 0;

Kernel::Kernel()
{
	init();
}

bool Kernel::init()
{
	timer = new Timer();
	settings = new Settings();

	return true;
}