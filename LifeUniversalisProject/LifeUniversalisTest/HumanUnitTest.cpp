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

	void allHumanParametersEqual(float refVal)
	{
		ASSERT_FLOAT_EQ(refVal, human.getSatiety());
		ASSERT_FLOAT_EQ(refVal, human.getHealth());
		ASSERT_FLOAT_EQ(refVal, human.getEntertainment());
		ASSERT_FLOAT_EQ(refVal, human.getEducation());
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
