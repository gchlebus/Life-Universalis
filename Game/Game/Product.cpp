#include "Product.h"

Product::Product(const std::string& name)
: _name(name)
{
  
}

const std::string& Product::getName() const
{
  return _name;
}

void Product::addAttribute(const std::string &attrName, float value)
{
  if (_isAttributePresent(attrName))
  {
    _attributeMap[attrName] += value;
  }
  else
  {
    _attributeMap[attrName] = value;
  }
}

const AttributeMap& Product::getAttributeMap() const
{
  return _attributeMap;
}

float Product::getAttributeValue(const std::string& attrName) const
{
  float val = 0;
  
  if (_isAttributePresent(attrName))
  {
    val = _attributeMap.at(attrName);
  }
  
  return val;
}

bool Product::_isAttributePresent(const std::string& attrName) const
{
  return _attributeMap.find(attrName) != _attributeMap.end();
}
