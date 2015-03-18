#include "Settings.h"


Settings::Settings(void)
{
	fixedFrameTime = 500.0 / 5.0;
	fixedTimestep = true;

	timeRatio = 60.0f * 5.0 * 5.0;

	humanMultiplierSatiety			= 1.0f / 24.0f;
	humanMultiplierEntertainment	= 1.0f / 48.0f;
	humanMultiplierHealth			= 1.0f / 240.0f;
	humanMultiplierEducation		= 1.0f / 2400.0f;
}


Settings::~Settings(void)
{
}
