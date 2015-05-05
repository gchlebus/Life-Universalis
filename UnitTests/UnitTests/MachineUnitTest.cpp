#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Machine.h"
#include "ServicePointMock.h"

class GivenMachine
    : public ::testing::Test
{
protected:
    Machine machine;
};

TEST_F(GivenMachine, WhenServicePointAdded_ThenServicePointsHaveSizeOfOne)
{
    ServicePointMock* servicePointMock = new ServicePointMock();
    machine.addServicePoint(servicePointMock);
    ASSERT_EQ(1, machine.getServicePoints().size());
}

TEST_F(GivenMachine, WhenServicePointAdded_ThenServicePointsParentSet)
{
    ServicePointMock* servicePointMock = new ServicePointMock();
    EXPECT_CALL(*servicePointMock, setParent(&machine));
    machine.addServicePoint(servicePointMock);
}

TEST_F(GivenMachine, WhenSameServicePointAddedTwice_ThenServicePointAddedOnlyOnce)
{
    ServicePointMock* servicePointMock = new ServicePointMock();
    machine.addServicePoint(servicePointMock);
    machine.addServicePoint(servicePointMock);
    ASSERT_EQ(1, machine.getServicePoints().size());
}

class GivenMachineWithServicePoint
    : public GivenMachine
{
protected:
    GivenMachineWithServicePoint()
    {
        servicePointMock = new ServicePointMock();
        machine.addServicePoint(servicePointMock);
    }

    ServicePointMock* servicePointMock;
};

TEST_F(GivenMachineWithServicePoint, WhenUpdateCalled_ThenServicePointUpdated)
{
    EXPECT_CALL(*servicePointMock, update());
    machine.update();
}