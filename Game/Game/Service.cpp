#include "Service.h"

Service::Service(const std::string& name)
: _name(name)
{
  
}

const std::string& Service::getName() const
{
  return _name;
}

void Service::addAttribute(const std::string& attrName, float value)
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

const AttributeMap& Service::getAttributeMap() const
{
  return _attributeMap;
}

float Service::getAttributeValue(const std::string& attrName) const
{
  float val = 0;
  
  if (_isAttributePresent(attrName))
  {
    val = _attributeMap.at(attrName);
  }
  
  return val;
}

bool Service::_isAttributePresent(const std::string& attrName) const
{
  return _attributeMap.find(attrName) != _attributeMap.end();
}
