#include <gtest/gtest.h>
#include "HumanAIRestNeedComponent.h"
#include "TestGameEngine.h"
#include "HumanAIMasterComponent.h"
#include "HumanTaskQueueComponent.h"

class HumanAIRestNeedComponentTestMock
    : public HumanAIRestNeedComponent
{
public:
    void setFulfillment(float value) { _fulfillment = value; }
    void setCurrentTask(HumanTaskPtr task) { _currentTask = task; }
};

class HumanTaskMock
: public HumanTask
{
public:
    virtual std::string getTaskName() { return ""; }
    virtual Vector3 getTarget() { return Vector3(0, 0, 0); }
    virtual void onUpdate() {}
    State getState() { return HumanTask::EXECUTING; }
};

class RestNeedTest
    : public ::testing::Test
{
protected:
    RestNeedTest()
    {
        shouldDeleteRestNeedComponent = true;
        engine.engine->kernel->settings->humanNeedRestTime = 1;
        restNeedComponent = new HumanAIRestNeedComponentTestMock();
    }

    virtual ~RestNeedTest()
    {
        if (shouldDeleteRestNeedComponent)
            delete restNeedComponent;
    }

    TestGameEngine engine;
    HumanAIRestNeedComponentTestMock* restNeedComponent;
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

class RestNeedInHumanContextTest
    : public RestNeedTest
{
protected:
    RestNeedInHumanContextTest()
    {
        shouldDeleteRestNeedComponent = false;
        createHuman();
    }

    void createHuman()
    {
        human.addComponent(restNeedComponent);
        human.addComponent(new HumanComponent("Marian", 40));
        human.addComponent(new HumanAIMasterComponent());
        taskQueue = new HumanTaskQueueComponent();
        human.addComponent(taskQueue);

    }

    GameObject human;
    HumanTaskQueueComponent* taskQueue;
};

TEST_F(RestNeedInHumanContextTest, OnUpdate_TaskIsAddedToQueue)
{
    restNeedComponent->onUpdate();
    ASSERT_NE(nullptr, taskQueue->getCurrentTask());
}

TEST_F(RestNeedInHumanContextTest, WhenTaskIsExecuting_AfterOnUpdateFulfillmentIncreases)
{
    HumanTaskPtr task(new HumanTaskMock());
    restNeedComponent->setCurrentTask(task);
    restNeedComponent->setFulfillment(0.5f);

    engine.setLastDelta(2.5);
    restNeedComponent->onUpdate();

    ASSERT_FLOAT_EQ(0.5 + 0.25, restNeedComponent->getFulfillment());
}
