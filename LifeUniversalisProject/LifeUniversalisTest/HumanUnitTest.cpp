#include <gtest\gtest.h>
#include "..\LifeUniversalis\Human.h"

class HumanTest : public ::testing::Test
{
protected:
	void setAllHumanParametersTo(float val)
	{
		human.setSatiety(val);
		human.setHealth(val);
		human.setEntertainment(val);
		human.setEducation(val);
	}

	void setAllHumanMultiplayers(float val)
	{
		human.setSatietyMultiplier(val);
		human.setHealthMultiplier(val);
		human.setEntertainmentMultiplier(val);
		human.setEducationMultiplier(val);
	}

	void allHumanParametersEqual(float refVal)
	{
		double epsilon = 1e-7;

		EXPECT_NEAR(refVal, human.getSatiety(), epsilon);
		EXPECT_NEAR(refVal, human.getHealth(), epsilon);
		EXPECT_NEAR(refVal, human.getEntertainment(), epsilon);
		EXPECT_NEAR(refVal, human.getEducation(), epsilon);
	}

	Human human;
};

TEST_F(HumanTest, DefaultConstructor_AllParametersZero)
{
  allHumanParametersEqual(0.f);
}

TEST_F(HumanTest, SetterFunctions_ParameterInZeroOneRange)
{
	setAllHumanParametersTo(0.5f);
	allHumanParametersEqual(0.5f);
}

TEST_F(HumanTest, SetterFunctions_ParameterLessThanZero)
{
	setAllHumanParametersTo(-0.1f);
	allHumanParametersEqual(0.f);
}

TEST_F(HumanTest, SetterFunctions_ParameterGreaterThanOne)
{
	setAllHumanParametersTo(1.1f);
	allHumanParametersEqual(1.0f);
}

TEST_F(HumanTest, ParametersDrop)
{
	float parametersTime = 100;
	setAllHumanMultiplayers(1 / parametersTime);
	setAllHumanParametersTo(1.f);

	human.update(parametersTime/4);
	allHumanParametersEqual(0.75f);

	human.update(parametersTime/2);
	allHumanParametersEqual(0.25f);

	human.update(0);
	allHumanParametersEqual(0.25f);

	human.update(parametersTime/4);
	allHumanParametersEqual(0.f);
}
