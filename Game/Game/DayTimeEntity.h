#pragma once

#include <GameEngine.h>
#include "EnvironmentEntitiesNames.h"

#define GD_YEAR     (365.25 * 24.0 * 60.0)
#define GD_MONTH    (30.4 * 24.0 * 60.0)
#define GD_DAY      (24.0 * 60.0)
#define GD_HOUR     (60.0)
#define GD_MINUTE   (1.0)
#define GD_SECOND   (1.0 / 60.0)

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
//		if(timeStamp >= 60.0 * 24.0 * 365.25)
        if(timeStamp >= GD_YEAR)
		{
//			year = timeStamp / (60.0 * 24.0 * 365.25);
            year = timeStamp / GD_YEAR;
			timeStamp -= (double)year * 60.0 * 24.0 * 365.25;
		}
//		if(timeStamp >= 60.0 * 24.0 * 30.4)
        if(timeStamp >= GD_MONTH)
		{
//			month = timeStamp / (60.0 * 24.0 * 30.4);
            month = timeStamp / GD_MONTH;
			timeStamp -= (double)month * 60.0 * 24.0 * 30.4;
		}
//		if(timeStamp >= 60.0 * 24.0)
        if(timeStamp >= GD_DAY)
		{
//			day = timeStamp / (60.0 * 24.0);
            day = timeStamp / GD_DAY;
			timeStamp -= (double)day * 60.0 * 24.0;
		}
//		if(timeStamp >= 60.0)
        if(timeStamp >= GD_HOUR)
		{
//			hour = timeStamp / 60.0;
            hour = timeStamp / GD_HOUR;
			timeStamp -= (double)hour * 60.0;
		}
		minute = timeStamp;
		timeStamp -= (double)minute;
		second = timeStamp * 60.0;
    }
    double getDayHour()
    {
        return (double)hour + (double)minute / 60.0 + (double)second / 60.0 / 60.0;
    }
    bool operator<(GameDate &a)
    {
        return this->time < a.time;
    }
    bool operator>(GameDate &a)
    {
        return this->time > a.time;
    }
    bool operator>=(GameDate &a)
    {
        return this->time >= a.time;
    }
    bool operator<=(GameDate &a)
    {
        return this->time <= a.time;
    }
    bool operator==(GameDate &a)
    {
        return this->time == a.time;
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