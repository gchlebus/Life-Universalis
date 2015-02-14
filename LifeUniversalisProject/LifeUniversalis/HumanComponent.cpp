#include "HumanComponent.h"
#include "GameEngine.h"
#include "Kernel.h"
#include "Settings.h"

HumanComponent::HumanComponent()
	: GameObjectComponent("HumanComponent")
{
	_satiety = 0.0f;
	_health = 0.0f;
	_entertainment = 0.0f;
	_education = 0.0f;
	_settings = GameEngine::engine()->kernel->settings;
    _workplace = nullptr;
}

void HumanComponent::onStart()
{

}

void HumanComponent::onUpdate()
{
	float gameTimeDelta = _settings->fixedFrameTime * _settings->timeRatio; // in ms
	gameTimeDelta /= 1000 * 60; //in h
	setHealth(_health - gameTimeDelta * _getSatietyModifiedHealthMultiplier());
	setSatiety(_satiety - gameTimeDelta * _settings->humanMultiplierSatiety);
	setEntertainment(_entertainment - gameTimeDelta * _settings->humanMultiplierEntertainment);
	setEducation(_education - gameTimeDelta * _settings->humanMultiplierEducation);
}

void HumanComponent::onAttachToParent()
{

}

void HumanComponent::onDetachFromParent()
{

}

void HumanComponent::onDelete()
{

}
void HumanComponent::onEnabled()
{
    
}
void HumanComponent::onDisabled()
{
    
}

void HumanComponent::setSatiety(const float satiety)
{
	_satiety = boost::algorithm::clamp(satiety, 0.f, 1.f);
}

const float HumanComponent::getSatiety() const
{
	return _satiety;
}

void HumanComponent::setHealth(const float health)
{
	_health = boost::algorithm::clamp(health, 0.f, 1.f);
}

const float HumanComponent::getHealth() const
{
	return _health;
}

void HumanComponent::setEntertainment(const float entertainment)
{
	_entertainment = boost::algorithm::clamp(entertainment, 0.f, 1.f);
}

const float HumanComponent::getEntertainment() const
{
	return _entertainment;
}

void HumanComponent::setEducation(const float education)
{
	_education = boost::algorithm::clamp(education, 0.f, 1.f);
}

const float HumanComponent::getEducation() const
{
	return _education;
}

float HumanComponent::_getSatietyModifiedHealthMultiplier()
{
	return (2.f - _satiety) * _settings->humanMultiplierHealth;
}
