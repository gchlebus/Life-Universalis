#include "Human.h"

#include <algorithm>

Human::Human()
{
	_satiety = 0.0f;
	_health = 0.0f;
	_entertainment = 0.0f;
	_education = 0.0f;
}

void Human::update(const float deltaTime)
{
	setHealth(_health - deltaTime * getSatietyModifiedHealthMultiplier());
	setSatiety(_satiety - deltaTime * _satietyMultiplier);
	setEntertainment(_entertainment - deltaTime * _entertainmentMultiplier);
	setEducation(_education - deltaTime * _educationMultiplier);
}

void Human::setSatiety(const float satiety)
{
	_satiety = clip(satiety, 0.f, 1.f);
}

void Human::setSatietyMultiplier(const float satietyMultiplayer)
{
	_satietyMultiplier = satietyMultiplayer;
}

const float Human::getSatiety() const
{
	return _satiety;
}

void Human::setHealth(const float health)
{
	_health = clip(health, 0.f, 1.f);
}

void Human::setHealthMultiplier(const float healthMultiplayer)
{
	_healthMultiplier = healthMultiplayer;
}

const float Human::getHealth() const
{
	return _health;
}

void Human::setEntertainment(const float entertainment)
{
	_entertainment = clip(entertainment, 0.f, 1.f);
}

void Human::setEntertainmentMultiplier(const float entertainmentMultiplayer)
{
	_entertainmentMultiplier = entertainmentMultiplayer;
}

const float Human::getEntertainment() const
{
	return _entertainment;
}

void Human::setEducation(const float education)
{
	_education = clip(education, 0.f, 1.f);
}

void Human::setEducationMultiplier(const float educationMultiplayer)
{
	_educationMultiplier = educationMultiplayer;
}

const float Human::getEducation() const
{
	return _education;
}

float Human::getSatietyModifiedHealthMultiplier()
{
	return (2.f - _satiety) * _healthMultiplier;
}

float Human::clip(float val, float lower, float upper)
{
	return std::min(upper, std::max(lower, val));
}
