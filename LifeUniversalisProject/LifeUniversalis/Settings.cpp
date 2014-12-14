#include "Settings.h"


Settings::Settings(void)
{
	timeRatio = 60.0f;

	humanMultiplierSatiety			= 1.0f / 24.0f;
	humanMultiplierEntertainment	= 1.0f / 48.0f;
	humanMultiplierHealth			= 1.0f / 240.0f;
	humanMultiplierEducation		= 1.0f / 2400.0f;
}


Settings::~Settings(void)
{
}
