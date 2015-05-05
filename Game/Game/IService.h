#pragma once

#include "GlobalHeaders.h"

class IServicePoint;

class IService
{
public:

    virtual ~IService() {}

    virtual unsigned int getPrice() = 0;

    virtual std::string getName() = 0;

    // Returns service usage time in game time minutes with given workplaceOccupation.
    // If workplaceOccupation < minimal workplaceOccupation then MAX_DBL is returned
    virtual double getUsageTime(size_t workplaceOccupation) = 0;

    virtual size_t getMinimalWorkplaceOccupation() = 0;

    virtual float getFulfillmentChange(const std::string& needName) = 0;
};