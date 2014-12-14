#pragma once
#include "LifeUniversalisSystem.h"
#include "GlobalHeaders.h"
#include "Updateable.h"

class LIFEUNIVERSALIS_EXPORT Human : public Updateable
{
public:
	Human();

	virtual void update(const float deltaTime);
	
	void setSatiety(const float satiety);
	//! \param satietyMultiplier - inverted number of game time hours needed 
	//! to drop satiety from 1 to 0.
	void setSatietyMultiplier(const float satietyMultiplier);
	const float getSatiety() const;
	void setHealth(const float health);
	//! \param healthMultiplier - inverted number of game time hours needed 
	//! to drop health from 1 to 0.
	void setHealthMultiplier(const float healthMultiplier);
	const float getHealth() const;
	void setEntertainment(const float entertainment);
	//! \param entertainmentMultiplier - inverted number of game time hours 
	//! needed to drop entertainment from 1 to 0.
	void setEntertainmentMultiplier(const float entertainmentMultiplier);
	const float getEntertainment() const;
	void setEducation(const float education);
	//! \param educationMultiplier - inverted number of game time hours needed 
	//! to drop education from 1 to 0.
	void setEducationMultiplier(const float educationMultiplier);
	const float getEducation() const;

private:
	float clip(float val, float lower, float upper);

	float _satiety;
	float _satietyMultiplier;
	float _health;
	float _healthMultiplier;
	float _entertainment;
	float _entertainmentMultiplier;
	float _education;
	float _educationMultiplier;
};
