#include "Service.h"
#include "Machine.h"

Service::Service(Machine* parent)
{
    _parent = parent;
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

void Service::setServiceTime(float min)
{
    _serviceTime = min;
}

float Service::getServiceTime() const
{
    return _serviceTime;
}

bool Service::_isAttributePresent(const std::string& attrName) const
{
    return _attributeMap.find(attrName) != _attributeMap.end();
}

Machine* Service::getParent()
{
    return _parent;
}
