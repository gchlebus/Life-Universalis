#pragma once

#include "GlobalHeaders.h"
#include "IService.h"

struct UsageTime
{
    size_t occupation;
    double min;

    bool operator<(const UsageTime& other) const
    {
        return occupation < other.occupation;
    }

    bool operator==(const UsageTime& other) const
    {
        return occupation == other.occupation;
    }
};

class Service
    : public IService
{
public:
    Service(const std::string& name);

    void setPrice(unsigned int price);

    virtual unsigned int getPrice() override;

    virtual std::string getName();

    void setUsageTime(size_t workplaceOccupation, double min);

    virtual double getUsageTime(size_t workplaceOccupation);

    void setMinimalWorkplaceOccupation(size_t minimalOccupation);

    virtual size_t getMinimalWorkplaceOccupation();

    void setFulfillmentChange(const std::string& needName, float value);

    virtual float getFulfillmentChange(const std::string& needName);

protected:
    std::string _name;
    unsigned int _price;
    size_t _minimalWorkplaceOccupation;
    std::map<std::string, float> _attributes;
    std::vector<UsageTime> _usageTimes;
};
