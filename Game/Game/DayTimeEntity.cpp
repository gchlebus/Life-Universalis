#include "DayTimeEntity.h"

DayTimeEntity::DayTimeEntity() : GameEnvironmentEntity(EN_DAYTIME)
{
    show = false;
}

DayTimeEntity::~DayTimeEntity(void)
{
}

void DayTimeEntity::onStart()
{
	gameDate = GameDate();
	delta = GameDate();
    
}

void DayTimeEntity::onUpdate()
{
	//Get physical time
	double lastDeltaTime = GameEngine::engine()->kernel->timer->getLastDelta();

	//Get gameTime in ms
	double gameTimeStamp = lastDeltaTime * GameEngine::engine()->kernel->settings->timeRatio;

	//Convert game time in minutes
	gameTimeStamp /= 1000.0 * 60.0;


	delta = GameDate(gameTimeStamp);
	gameDate = GameDate(gameDate.time + gameTimeStamp);
    
    if(show)
    {
        LOG("\nGameTime:");
        LOGF(F("Absolute:"));
        LOGF(F("\tYear: %1%") % gameDate.year);
        LOGF(F("\tMonth: %1%") % gameDate.month);
        LOGF(F("\tDay: %1%") % gameDate.day);
        LOGF(F("\tHour: %1%") % gameDate.hour);
        LOGF(F("\tMinute: %1%") % gameDate.minute);
        LOGF(F("\tSecond: %1%") % gameDate.second);
        LOGF(F("\tTime: %1%") % gameDate.time);
        
        LOG("Delta:");
        LOGF(F("\tYear: %1%") % delta.year);
        LOGF(F("\tMonth: %1%") % delta.month);
        LOGF(F("\tDay: %1%") % delta.day);
        LOGF(F("\tHour: %1%") % delta.hour);
        LOGF(F("\tMinute: %1%") % delta.minute);
        LOGF(F("\tSecond: %1%") % delta.second);
        LOGF(F("\tTime: %1%") % delta.time);
        show = false;
    }
}

void DayTimeEntity::onStop()
{
}

GameDate DayTimeEntity::getCurrentGameDate()
{
	return gameDate;
}
GameDate DayTimeEntity::getLastDelta()
{
	return delta;
}