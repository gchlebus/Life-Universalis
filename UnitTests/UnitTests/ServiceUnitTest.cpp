#include <gtest/gtest.h>
#include "Service.h"

class ServiceTest
    : public testing::Test
{
protected:
    Service service;
};

TEST_F(ServiceTest, OnGetNotPresentAttribute_ReturnsZero)
{
    ASSERT_FLOAT_EQ(0.f, service.getAttributeValue("bla"));
}

TEST_F(ServiceTest, OnGetPresentAttribute_ReturnsAttributeValue)
{
    std::string attrName = "bla";
    float value = 5;

    service.addAttribute(attrName, value);

    ASSERT_FLOAT_EQ(value, service.getAttributeValue(attrName));
}

TEST_F(ServiceTest, OnAddTwiceTheSameAttribute_ReturnsAccumulatedValue)
{
    std::string attrName = "bla";
    float value = 5;

    service.addAttribute(attrName, value);
    service.addAttribute(attrName, value);

    ASSERT_FLOAT_EQ(2 * value, service.getAttributeValue(attrName));
}
