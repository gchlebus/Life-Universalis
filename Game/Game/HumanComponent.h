#pragma once

#include <GameEngine.h>

class Workplace;

class HumanComponent
	: public GameObjectComponent
{
public:
	HumanComponent();

    void onStart();
    void onBeforeFirstUpdate();
	void onUpdate();
	void onAttachToParent();
	void onDetachFromParent();
    void onDelete();
    void onEnabled();
    void onDisabled();

	void setSatiety(const float satiety);
	const float getSatiety() const;
	void setHealth(const float health);
	const float getHealth() const;
	void setEntertainment(const float entertainment);
	const float getEntertainment() const;
	void setEducation(const float education);
	const float getEducation() const;

private:
	float _getSatietyModifiedHealthMultiplier();

	float _satiety;
	float _health;
	float _entertainment;
	float _education;
	Settings *_settings;
    Workplace *_workplace;
    
};
