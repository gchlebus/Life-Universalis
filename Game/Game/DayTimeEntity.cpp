#include "DayTimeEntity.h"

DayTimeEntity::DayTimeEntity() : GameEnvironmentEntity("DayTime")
{
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

	std::cout	<< "\nGameTime:\n"
				<< "Absolute:"

				<< "\n\tYear: " << gameDate.year
				<< "\n\tMonth: " << gameDate.month
				<< "\n\tDay: " << gameDate.day
				<< "\n\tHour: " << gameDate.hour
				<< "\n\tMinute: " << gameDate.minute
				<< "\n\tSecond: " << gameDate.second
				<< "\n\tTime: " << gameDate.time

				<< "\nDelta:"
				<< "\n\tYear: " << delta.year
				<< "\n\tMonth: " << delta.month
				<< "\n\tDay: " << delta.day
				<< "\n\tHour: " << delta.hour
				<< "\n\tMinute: " << delta.minute
				<< "\n\tSecond: " << delta.second
				<< "\n\tTime: " << delta.time << "\n";
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