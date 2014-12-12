#include <gtest\gtest.h>
#include "..\LifeUniversalis\Human.h"

TEST(HumanTest, DefaultConstructor_AllParametersZero)
{
  Human human;
  ASSERT_FLOAT_EQ(0.f, human.satiety);
  ASSERT_FLOAT_EQ(0.f, human.health);
  ASSERT_FLOAT_EQ(0.f, human.entertainment);
  ASSERT_FLOAT_EQ(0.f, human.education);
}