#pragma once
#include "GlobalHeaders.h"


class GAMEENGINE_EXPORT Settings
{
public:
	Settings(void);
	~Settings(void);
	//Frame settings
    double fixedFrameTime; // real time ms
	bool fixedTimestep;

	//Global settings
    float timeRatio; // game_time / real_time ratio

	//Human settings (stats are based on GameTime)
	float humanMultiplierSatiety;
	float humanMultiplierEntertainment;
	float humanMultiplierHealth;
	float humanMultiplierEducation;

    // Time game time hours to drop parameter from max to min.
    float humanNeedRestTime;
};

