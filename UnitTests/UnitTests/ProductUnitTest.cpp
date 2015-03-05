#include <gtest/gtest.h>
#include "Service.h"

class ProductTest : public testing::Test
{
protected:
  ProductTest() : p("") { }

    Service p;
};

TEST_F(ProductTest, ProductName)
{
  std::string name = "Prod";
Service prod(name);
  
  ASSERT_EQ(name, prod.getName());
}

TEST_F(ProductTest, OnGetNotPresentAttribute_ReturnsZero)
{
  ASSERT_FLOAT_EQ(0.f, p.getAttributeValue("bla"));
}

TEST_F(ProductTest, OnGetPresentAttribute_ReturnsAttributeValue)
{
  std::string attrName = "bla";
  float value = 5;
  
  p.addAttribute(attrName, value);
  
  ASSERT_FLOAT_EQ(value, p.getAttributeValue(attrName));
}

TEST_F(ProductTest, OnAddTwiceTheSameAttribute_ReturnsAccumulatedValue)
{
  std::string attrName = "bla";
  float value = 5;
  
  p.addAttribute(attrName, value);
  p.addAttribute(attrName, value);
  
  ASSERT_FLOAT_EQ(2*value, p.getAttributeValue(attrName));
}
