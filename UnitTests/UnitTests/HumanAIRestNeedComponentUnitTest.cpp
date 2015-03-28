#include <gtest/gtest.h>
#include "HumanAIRestNeedComponent.h"
#include "TestGameEngine.h"
#include "HumanComponent.h"
#include "MotionComponent.h"

class RestNeedTest
    : public ::testing::Test
{
protected:
    RestNeedTest()
    {
        shouldDeleteRestNeedComponent = true;
        engine.engine->kernel->settings->humanNeedRestTime = 1;
        restNeedComponent = new HumanAIRestNeedComponent();
    }

    virtual ~RestNeedTest()
    {
        if (shouldDeleteRestNeedComponent)
            delete restNeedComponent;
    }

    TestGameEngine engine;
    HumanAIRestNeedComponent* restNeedComponent;
    bool shouldDeleteRestNeedComponent;
};


TEST_F(RestNeedTest, NeedName)
{
    ASSERT_STREQ("Rest", restNeedComponent->getNeedName().c_str());
}

TEST_F(RestNeedTest, Constructor_InitialParamaterValues)
{
    ASSERT_FLOAT_EQ(1.f, restNeedComponent->getFulfillment());
    ASSERT_FLOAT_EQ(0.f, restNeedComponent->getPriority());
}

TEST_F(RestNeedTest, ParameterValuesDropAfterHalfHour)
{
    engine.setTime(30);
    restNeedComponent->updateStats();

    ASSERT_FLOAT_EQ(0.5f, restNeedComponent->getFulfillment());
    ASSERT_FLOAT_EQ(25.f, restNeedComponent->getPriority());
}

class HumanTiredRestNeedTest
    : public RestNeedTest
{
protected:
    HumanTiredRestNeedTest()
    {
        shouldDeleteRestNeedComponent = false;
        engine.setTime(30);
        restNeedComponent->updateStats();
        createHuman();
    }

    void createHuman()
    {
        motionComponent = new MotionComponent();
        humanComponent = new HumanComponent("Marian", 40);
        humanComponent->setHome(&home);

        human.addComponent(restNeedComponent);
        human.addComponent(motionComponent);
        human.addComponent(humanComponent);
    }

    GameObject human;
    GameObject home;
    MotionComponent* motionComponent;
    HumanComponent* humanComponent;
};

TEST_F(HumanTiredRestNeedTest, WhenHumanNotAtHome_AfterOnUpdateHomeIsSetAsTarget)
{
    Vector3 humanPosition = Vector3(0, 0, 0);
    Vector3 homePosition = Vector3(1, 1, 1);
    human.getTransform().setWorldPosition(humanPosition);
    home.getTransform().setWorldPosition(homePosition);

    restNeedComponent->onUpdate();

    ASSERT_FLOAT_EQ(0.f, (homePosition - motionComponent->getTargetPosition()).norm());
}

TEST_F(HumanTiredRestNeedTest, WhenHumanNotAtHome_AfterOnUpdateFulfillmentIsNotChanged)
{
    human.getTransform().setWorldPosition(Vector3(0, 0, 0));
    home.getTransform().setWorldPosition(Vector3(1, 1, 1));
    float prevFulfillment = restNeedComponent->getFulfillment();

    restNeedComponent->onUpdate();

    ASSERT_FLOAT_EQ(prevFulfillment, restNeedComponent->getFulfillment());
}

TEST_F(HumanTiredRestNeedTest, WhenHumanAtHome_AfterOnUpdateFulfillmentIncreases)
{
    human.getTransform().setWorldPosition(Vector3(0, 0, 0));
    home.getTransform().setWorldPosition(Vector3(0, 0, 0));
    float prevFulfillment = restNeedComponent->getFulfillment();

    restNeedComponent->onUpdate();

    ASSERT_LT(prevFulfillment, restNeedComponent->getFulfillment());
}

TEST_F(HumanTiredRestNeedTest, WhenHumanAtHome_AfterUpdateStatsFulfillmentIsNotChanged)
{
    human.getTransform().setWorldPosition(Vector3(0, 0, 0));
    home.getTransform().setWorldPosition(Vector3(0, 0, 0));
    restNeedComponent->onUpdate();
    float prevFulfillment = restNeedComponent->getFulfillment();

    engine.setTime(30);
    restNeedComponent->updateStats();

    ASSERT_EQ(prevFulfillment, restNeedComponent->getFulfillment());
}