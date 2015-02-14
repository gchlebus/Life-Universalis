#include "HumanParametersComponent.h"
#include "GameEngine.h"
#include "Kernel.h"
#include "Settings.h"

HumanParametersComponent::HumanParametersComponent()
	: GameObjectComponent("HumanParametersComponent")
{
	_satiety = 0.0f;
	_health = 0.0f;
	_entertainment = 0.0f;
	_education = 0.0f;
	_settings = GameEngine::engine()->kernel->settings;
}

void HumanParametersComponent::onStart()
{

}

void HumanParametersComponent::onUpdate()
{
	float gameTimeDelta = _settings->fixedFrameTime * _settings->timeRatio; // in ms
	gameTimeDelta /= 1000 * 60; //in h
	setHealth(_health - gameTimeDelta * _getSatietyModifiedHealthMultiplier());
	setSatiety(_satiety - gameTimeDelta * _settings->humanMultiplierSatiety);
	setEntertainment(_entertainment - gameTimeDelta * _settings->humanMultiplierEntertainment);
	setEducation(_education - gameTimeDelta * _settings->humanMultiplierEducation);
}

void HumanParametersComponent::onAttachToParent()
{

}

void HumanParametersComponent::onDetachFromParent()
{

}

void HumanParametersComponent::onDelete()
{

}

void HumanParametersComponent::setSatiety(const float satiety)
{
	_satiety = boost::algorithm::clamp(satiety, 0.f, 1.f);
}

const float HumanParametersComponent::getSatiety() const
{
	return _satiety;
}

void HumanParametersComponent::setHealth(const float health)
{
	_health = boost::algorithm::clamp(health, 0.f, 1.f);
}

const float HumanParametersComponent::getHealth() const
{
	return _health;
}

void HumanParametersComponent::setEntertainment(const float entertainment)
{
	_entertainment = boost::algorithm::clamp(entertainment, 0.f, 1.f);
}

const float HumanParametersComponent::getEntertainment() const
{
	return _entertainment;
}

void HumanParametersComponent::setEducation(const float education)
{
	_education = boost::algorithm::clamp(education, 0.f, 1.f);
}

const float HumanParametersComponent::getEducation() const
{
	return _education;
}

float HumanParametersComponent::_getSatietyModifiedHealthMultiplier()
{
	return (2.f - _satiety) * _settings->humanMultiplierHealth;
}
