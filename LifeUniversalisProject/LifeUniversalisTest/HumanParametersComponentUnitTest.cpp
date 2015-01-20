#include <gtest\gtest.h>
#include <cmath>

#include "..\LifeUniversalis\HumanParametersComponent.h"
#include "..\LifeUniversalis\GameEngine.h"
#include "..\LifeUniversalis\Kernel.h"
#include "..\LifeUniversalis\Settings.h"


class HumanParametersComponentTest : public ::testing::Test
{
protected:
	void SetUp()
	{
		settings = GameEngine::engine()->kernel->settings;
	}

	void setAllParametersTo(float val)
	{
		component.setEducation(val);
		component.setEntertainment(val);
		component.setHealth(val);
		component.setSatiety(val);
	}

	void allParametersEqual(float refVal)
	{
		EXPECT_EQ(refVal, component.getEducation());
		EXPECT_EQ(refVal, component.getEntertainment());
		EXPECT_EQ(refVal, component.getSatiety());
		EXPECT_EQ(refVal, component.getHealth());
	}

	//! \return Minimum number of onUpdate() calls to drop parameter from 1 to 0.
	unsigned int getParameterIterations(const float parameterMultipier)
	{
		double parameterTime = 1 / parameterMultipier; // in game time hours
		parameterTime /= settings->timeRatio; // in real time hours
		parameterTime *= 60 * 1000; // in real time ms
		return static_cast<unsigned int>(ceil(parameterTime / settings->fixedFrameTime));
	}

	HumanParametersComponent component;
	Settings *settings;
};

TEST_F(HumanParametersComponentTest, NameTest)
{	
	ASSERT_EQ("HumanParametersComponent", component.getName());
}

TEST_F(HumanParametersComponentTest, ConstructorTest_AllParametersZero)
{
	allParametersEqual(0.f);
}

TEST_F(HumanParametersComponentTest, Setters_OnSetValuesInValidRange_RetrievedValuesAreTheSame)
{
	setAllParametersTo(0.5f);
	allParametersEqual(0.5f);
}

TEST_F(HumanParametersComponentTest, Setters_OnSetValuesLessThanZero_RetrievedValuesAreZero)
{
	setAllParametersTo(-0.1f);
	allParametersEqual(0.f);
}

TEST_F(HumanParametersComponentTest, Setters_OnSetValuesGreaterThanOne_RetrievedValuesAreOne)
{
	setAllParametersTo(1.1f);
	allParametersEqual(1.0f);
}

TEST_F(HumanParametersComponentTest, EducationDropInTime)
{
	const unsigned int iterations = getParameterIterations(settings->humanMultiplierEducation);

	component.setEducation(1.f);
	for (unsigned int i = 0; i < iterations/2; ++i)
	{
		component.onUpdate();
	}
	ASSERT_NEAR(0.5f, component.getEducation(), 1e-3);
}

TEST_F(HumanParametersComponentTest, EntertainmentDropInTime)
{
	const unsigned int iterations = getParameterIterations(settings->humanMultiplierEntertainment);

	component.setEntertainment(1.f);
	for (unsigned int i = 0; i < iterations/2; ++i)
	{
		component.onUpdate();
	}
	ASSERT_NEAR(0.5f, component.getEntertainment(), 1e-3);
}

TEST_F(HumanParametersComponentTest, SatietyDropInTime)
{
	const unsigned int iterations = getParameterIterations(settings->humanMultiplierSatiety);

	component.setSatiety(1.f);
	for (unsigned int i = 0; i < iterations/2; ++i)
	{
		component.onUpdate();
	}
	ASSERT_NEAR(0.5f, component.getSatiety(), 1e-3);
}

TEST_F(HumanParametersComponentTest, HealthDropInTime)
{
	const unsigned int iterations = getParameterIterations(settings->humanMultiplierHealth);

	component.setHealth(1.f);
	component.setSatiety(1.f);
	for (unsigned int i = 0; i < iterations/2; ++i)
	{
		component.onUpdate();
		component.setSatiety(1.f); // ensure that health drops at normal rate
	}
	ASSERT_NEAR(0.5f, component.getHealth(), 1e-3);

	component.setHealth(1.f);
	component.setSatiety(0.f); // health drops twice as fast
	for (unsigned int i = 0; i < iterations/4; ++i)
	{
		component.onUpdate();
	}
	ASSERT_NEAR(0.5f, component.getHealth(), 1e-3);
}
