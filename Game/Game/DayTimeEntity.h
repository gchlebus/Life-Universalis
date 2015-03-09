#pragma once

#include <GameEngine.h>
#include "EnvironmentEntitiesNames.h"

//Timestamp is the number of minutes IN GAME
struct GameDate
{
	GameDate(double timeStamp = 0.0)
	{
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		second = 0;


		time = timeStamp; //It's time in game minutes
		if(timeStamp >= 60.0 * 24.0 * 365.25)
		{
			year = timeStamp / (60.0 * 24.0 * 365.25);
			timeStamp -= (double)year * 60.0 * 24.0 * 365.25;
		}
		if(timeStamp >= 60.0 * 24.0 * 30.4)
		{
			month = timeStamp / (60.0 * 24.0 * 30.4);
			timeStamp -= (double)month * 60.0 * 24.0 * 30.4;
		}
		if(timeStamp >= 60.0 * 24.0)
		{
			day = timeStamp / (60.0 * 24.0);
			timeStamp -= (double)day * 60.0 * 24.0;
		}
		if(timeStamp >= 60.0)
		{
			hour = timeStamp / 60.0;
			timeStamp -= (double)hour * 60.0;
		}
		minute = timeStamp;
		timeStamp -= (double)minute;
		second = timeStamp * 60.0;
    }
    bool operator<(GameDate &a)
    {
        return this->time < a.time;
    }
    bool operator>(GameDate &a)
    {
        return this->time > a.time;
    }
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	double time;
};

class DayTimeEntity : public GameEnvironmentEntity
{
public:
	DayTimeEntity();
	~DayTimeEntity(void);

	void onStart();
	void onUpdate();
	void onStop();

	GameDate getCurrentGameDate();
	GameDate getLastDelta();
protected:
	GameDate gameDate;
	GameDate delta;
};