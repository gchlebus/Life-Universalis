#include "Service.h"

Service::Service(const std::string& name)
    : _name(name)
    , _price(0)
    , _minimalWorkplaceOccupation(1)
{

}

void Service::setPrice(unsigned int price)
{
    _price = price;
}

unsigned int Service::getPrice()
{
    return _price;
}

void Service::setFulfillmentChange(const std::string& needName, float value)
{
    _attributes[needName] = value;
}

float Service::getFulfillmentChange(const std::string& needName)
{
    return _attributes[needName];
}

void Service::setMinimalWorkplaceOccupation(size_t minimalOccupation)
{
    _minimalWorkplaceOccupation = minimalOccupation;
}

size_t Service::getMinimalWorkplaceOccupation()
{
    return _minimalWorkplaceOccupation;
}

void Service::setUsageTime(size_t workplaceOccupation, double min)
{
    UsageTime usageTime = {workplaceOccupation, min};
    auto it = std::find(_usageTimes.begin(), _usageTimes.end(), usageTime);

    if (it == _usageTimes.end())
        _usageTimes.push_back(usageTime);
    else
        it->min = min;

    std::sort(_usageTimes.begin(), _usageTimes.end());
}

double Service::getUsageTime(size_t workplaceOccupation)
{
    if (workplaceOccupation < _minimalWorkplaceOccupation)
        return std::numeric_limits<double>::max();

    UsageTime usageTime = {workplaceOccupation, 0};
    auto it = std::lower_bound(_usageTimes.begin(), _usageTimes.end(), usageTime);

    if (it == _usageTimes.end())
        return _usageTimes.back().min;
    else if (it == _usageTimes.begin())
        return _usageTimes.front().min;

    if (usageTime.occupation == it->occupation)
    {
        return it->min;
    }

    double a = (it->min - (it-1)->min) / (it->occupation - (it-1)->occupation);
    double b = it->min - a*it->occupation;
    return a*usageTime.occupation + b;
}

std::string Service::getName()
{
    return _name;
}
