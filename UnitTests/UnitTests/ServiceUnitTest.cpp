#include <gtest/gtest.h>
#include "Service.h"

class GivenService
    : public testing::Test
{
protected:
    GivenService()
        : service("Wurst")
    {

    }
    Service service;
};

TEST_F(GivenService, GetServiceName)
{
    ASSERT_EQ("Wurst", service.getName());
}

TEST_F(GivenService, PriceAccessors)
{
    const int price = 10;
    service.setPrice(price);
    ASSERT_EQ(price, service.getPrice());
}

TEST_F(GivenService, MinimalWorkplaceOccupationAccessors)
{
    const int occupation = 3;
    service.setMinimalWorkplaceOccupation(occupation);
    ASSERT_EQ(occupation, service.getMinimalWorkplaceOccupation());
}

TEST_F(GivenService, FulfillmentChangeAccesors)
{
    char const* const needName = "Durst";
    const int value = 10;
    service.setFulfillmentChange(needName, value);
    ASSERT_EQ(value, service.getFulfillmentChange(needName));
}

TEST_F(GivenService, WhenNotPresentFulfillmentChangeAccesed_ThenZeroReturned)
{
    ASSERT_EQ(0, service.getFulfillmentChange("NotPresentNeed"));
}

TEST_F(GivenService, WhenOccupationLowerThanMinimal_ThenMaxDblReturned)
{
    service.setMinimalWorkplaceOccupation(2);
    ASSERT_DOUBLE_EQ(DBL_MAX, service.getUsageTime(1));
}

TEST_F(GivenService, UsageTimeAccesors)
{
    service.setUsageTime(1, 60);
    ASSERT_DOUBLE_EQ(60, service.getUsageTime(1));
}

TEST_F(GivenService, WhenThrowingShitAtSetUsageTime_ThenGetUsageTimeReturnsCorrectly)
{
    service.setUsageTime(2, 20);
    service.setUsageTime(2, 30);
    service.setUsageTime(2, 40);
    service.setUsageTime(2, 30);
    ASSERT_DOUBLE_EQ(30, service.getUsageTime(2));
}

TEST_F(GivenService,
    WhenGivenOccupationIsGreaterThanManuallySet_ThenUsageTimeForMaximumOccupationReturned)
{
    service.setUsageTime(1, 60);
    ASSERT_DOUBLE_EQ(60, service.getUsageTime(3));
}

TEST_F(GivenService,
    WhenGivenOccupationIsLowerThanManuallySet_ThenUsageTimeForMinimalOccupationReturned)
{
    service.setUsageTime(2, 60);
    ASSERT_DOUBLE_EQ(60, service.getUsageTime(1));
}

TEST_F(GivenService, WhenAskedOccupationIsInBetween_ThenLinearInterpolationHappens)
{
    service.setUsageTime(2, 20);
    service.setUsageTime(4, 40);
    ASSERT_DOUBLE_EQ(30, service.getUsageTime(3));
}