#include "../LifeUniversalis/Transform.h"

#include <gtest/gtest.h>

TEST(TransformTest, ConstructorTest_LocalPositionZero)
{
	Transform transform;
	
	ASSERT_FLOAT_EQ(0.f, transform.getLocalPosition().x());
	ASSERT_FLOAT_EQ(0.f, transform.getLocalPosition().y());
	ASSERT_FLOAT_EQ(0.f, transform.getLocalPosition().z());
}

TEST(TransformTest, ConstructorTest_LocalEulerAnglesZero)
{
	Transform transform;
	
	ASSERT_FLOAT_EQ(0.f, transform.getLocalEulerAngles().x());
	ASSERT_FLOAT_EQ(0.f, transform.getLocalEulerAngles().y());
	ASSERT_FLOAT_EQ(0.f, transform.getLocalEulerAngles().z());
}

TEST(TransformTest, ConstructorTest_LocalScaleOne)
{
	Transform transform;
	
	ASSERT_FLOAT_EQ(1.f, transform.getLocalScale().x());
	ASSERT_FLOAT_EQ(1.f, transform.getLocalScale().y());
	ASSERT_FLOAT_EQ(1.f, transform.getLocalScale().z());
}

TEST(TransformTest, Translation)
{
	Transform transform;

	transform.translate(Vector3(1.f, 2.f, 3.f));

	ASSERT_FLOAT_EQ(1.f, transform.getLocalPosition().x());
	ASSERT_FLOAT_EQ(2.f, transform.getLocalPosition().y());
	ASSERT_FLOAT_EQ(3.f, transform.getLocalPosition().z());
}

TEST(TransformTest, RotationEulerAngles)
{
	Transform transform;
	Vector3 eulerAngles((float)M_PI/8, (float)M_PI/4, (float)M_PI/2);

	transform.rotate(eulerAngles);

	EXPECT_FLOAT_EQ(eulerAngles.x(), transform.getLocalEulerAngles().x());
	EXPECT_FLOAT_EQ(eulerAngles.y(), transform.getLocalEulerAngles().y());
	EXPECT_FLOAT_EQ(eulerAngles.z(), transform.getLocalEulerAngles().z());
}

TEST(TransformTest, RotationAngleAxis)
{
	Transform transform;
	Vector3 axis(1.f, 0.f, 0.f);
	float angle = (float)M_PI/4;

	transform.rotate(axis, angle);

	EXPECT_FLOAT_EQ(angle, transform.getLocalEulerAngles().x());
	EXPECT_FLOAT_EQ(0.f, transform.getLocalEulerAngles().y());
	EXPECT_FLOAT_EQ(0.f, transform.getLocalEulerAngles().z());
}

TEST(TransformTest, ParentChild_GetWorldPosition)
{
	Transform parent, child;
	child.setParent(&parent);

	parent.setLocalPosition(Vector3(1, 2, 3));

	EXPECT_FLOAT_EQ(1.f, child.getWorldPosition().x());
	EXPECT_FLOAT_EQ(2.f, child.getWorldPosition().y());
	EXPECT_FLOAT_EQ(3.f, child.getWorldPosition().z());

	parent.reset();
	parent.rotate(Vector3(0, 0, (float)M_PI/2));
	child.setLocalPosition(Vector3(1, 1, 0));

	EXPECT_FLOAT_EQ(-1.f, child.getWorldPosition().x());
	EXPECT_FLOAT_EQ(1.f, child.getWorldPosition().y());
	EXPECT_FLOAT_EQ(0.f, child.getWorldPosition().z());
}

TEST(TransformTest, ParentChild_SetWorldPosition)
{
	Transform parent, child;
	child.setParent(&parent);

	parent.setLocalPosition(Vector3(1, 2, 3));
	child.setWorldPosition(Vector3::Zero());

	EXPECT_FLOAT_EQ(-1.f, child.getLocalPosition().x());
	EXPECT_FLOAT_EQ(-2.f, child.getLocalPosition().y());
	EXPECT_FLOAT_EQ(-3.f, child.getLocalPosition().z());
}

TEST(TransformTest, ParentChild_GetWorldEulerAngles)
{
	Transform parent, child;
	child.setParent(&parent);
	float angle = (float)M_PI/8;

	parent.setLocalEulerAngles(Vector3(0, 0, angle));
	child.setLocalEulerAngles(Vector3(0, 0, angle));

	EXPECT_FLOAT_EQ(0.f, child.getWorldEulerAngles().x());
	EXPECT_FLOAT_EQ(0.f, child.getWorldEulerAngles().y());
	EXPECT_FLOAT_EQ(2*angle, child.getWorldEulerAngles().z());
}

TEST(TransformTest, ParentChild_SetWorldEulerAngles)
{
	Transform parent, child, grandchid;
	child.setParent(&parent);
	grandchid.setParent(&child);
	grandchid.setLocalPosition(Vector3(1, 1, 0));

	parent.setLocalEulerAngles(Vector3(0, 0,(float)M_PI/2));
	child.setWorldEulerAngles(Vector3(0, 0, 0));

	EXPECT_FLOAT_EQ(1.f, grandchid.getWorldPosition().x());
	EXPECT_FLOAT_EQ(1.f, grandchid.getWorldPosition().y());
	EXPECT_FLOAT_EQ(0, grandchid.getWorldPosition().z());
}

TEST(TransformTest, FromForwardLeftPosition)
{
	Transform parent, child;
	child.setParent(&parent);
	child.setLocalPosition(Vector3(1, 0, 1));

	parent.fromForwardLeftPosition(Vector3(1, 0, 1), Vector3(1, 0, -1), Vector3(0, 0, 0));

	float eps = (float)1e-6;
	EXPECT_NEAR(1.4142135f, child.getWorldPosition().x(), eps);
	EXPECT_NEAR(0.f, child.getWorldPosition().y(), eps);
	EXPECT_NEAR(0.f, child.getWorldPosition().z(), eps);
}
