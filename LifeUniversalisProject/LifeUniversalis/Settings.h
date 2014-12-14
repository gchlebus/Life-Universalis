#pragma once
#include "GlobalHeaders.h"


class LIFEUNIVERSALIS_EXPORT Settings
{
public:
	Settings(void);
	~Settings(void);

	//Global settings
	float timeRatio;

	//Human settings (stats are based on GameTime)
	float humanMultiplierSatiety;
	float humanMultiplierEntertainment;
	float humanMultiplierHealth;
	float humanMultiplierEducation;
};

