#pragma once
#include "LifeUniversalisSystem.h"
#include "GlobalHeaders.h"
#include "Updateable.h"

class LIFEUNIVERSALIS_EXPORT Human : public Updateable
{
public:
	Human();
	void update(double ms);
	
	void setSatiety(const float satiety);
	const float getSatiety() const;
	void setHealth(const float health);
	const float getHealth() const;
	void setEntertainment(const float entertainment);
	const float getEntertainment() const;
	void setEducation(const float education);
	const float getEducation() const;

private:
	float clip(float val, float lower, float upper);

	float _satiety;
	float _health;
	float _entertainment;
	float _education;
};