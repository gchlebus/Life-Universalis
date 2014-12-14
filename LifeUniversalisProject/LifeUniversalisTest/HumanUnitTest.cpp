#include <gtest\gtest.h>

#include "..\LifeUniversalis\Human.h"

class HumanTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		epsilon = 1e-7;
	}

	void setAllHumanParametersTo(float val)
	{
		human.setSatiety(val);
		human.setHealth(val);
		human.setEntertainment(val);
		human.setEducation(val);
	}

	void setAllHumanMultipliers(float val)
	{
		human.setSatietyMultiplier(val);
		human.setHealthMultiplier(val);
		human.setEntertainmentMultiplier(val);
		human.setEducationMultiplier(val);
	}

	void allHumanParametersEqual(float refVal)
	{
		humanHealthEquals(refVal);
		allNonHealthHumanParametersEqual(refVal);		
	}

	void humanHealthEquals(float refVal)
	{
		EXPECT_NEAR(refVal, human.getHealth(), epsilon);
	}

	void allNonHealthHumanParametersEqual(float refVal)
	{
		EXPECT_NEAR(refVal, human.getSatiety(), epsilon);
		EXPECT_NEAR(refVal, human.getEntertainment(), epsilon);
		EXPECT_NEAR(refVal, human.getEducation(), epsilon);
	}

	Human human;
	double epsilon;
};

TEST_F(HumanTest, DefaultConstructor_AllParametersZero)
{
	allHumanParametersEqual(0.f);
}

TEST_F(HumanTest, Setters_OnSetValuesInValidRange_RetrievedValuesAreTheSame)
{
	setAllHumanParametersTo(0.5f);
	allHumanParametersEqual(0.5f);
}

TEST_F(HumanTest, Setters_OnSetValuesLessThanZero_RetrievedValuesAreZero)
{
	setAllHumanParametersTo(-0.1f);
	allHumanParametersEqual(0.f);
}

TEST_F(HumanTest, Setters_OnSetValuesGreaterThanOne_RetrievedValuesAreOne)
{
	setAllHumanParametersTo(1.1f);
	allHumanParametersEqual(1.0f);
}

TEST_F(HumanTest, NonHealthParametersDrop)
{
	float parametersTime = 100;
	setAllHumanMultipliers(1 / parametersTime);
	
	setAllHumanParametersTo(1.f);
	human.update(0.25f * parametersTime);
	allNonHealthHumanParametersEqual(1.f - 0.25f);

	setAllHumanParametersTo(1.f);
	human.update(0.5f * parametersTime);
	allNonHealthHumanParametersEqual(1.f - 0.5f);

	setAllHumanParametersTo(1.f);
	human.update(1.f * parametersTime);
	allNonHealthHumanParametersEqual(1.f - 1.f);

	setAllHumanParametersTo(1.f);
	human.update(0.f);
	allNonHealthHumanParametersEqual(1.f);
}

TEST_F(HumanTest, HealthDrop)
{
	float healthTime = 100;
	human.setHealthMultiplier(1 / healthTime);
	
	human.setHealth(1.f);
	human.setSatiety(1.f); // health drops at normal rate
	human.update(0.5f * healthTime);
	humanHealthEquals(1.f - 1.f * 0.5f);

	human.setHealth(1.f);
	human.setSatiety(0.f); // now health drops 2x faster
	human.update(0.5f * healthTime);
	humanHealthEquals(1.f - 2.f * 0.5f);

	human.setHealth(1.f);
	human.setSatiety(0.5f); // now health drops 1.5x faster
	human.update(0.5f * healthTime);
	humanHealthEquals(1.f - 1.5f * 0.5f);
}
