#pragma once

#include <gmock/gmock.h>

#include "IService.h"

class ServiceMock
    : public IService
{
public:
    MOCK_METHOD0(getServicePoint, IServicePoint*());

    MOCK_METHOD0(getPrice, unsigned int());

    MOCK_METHOD0(getName, std::string());

    MOCK_METHOD1(getFulfillmentChange, float(const std::string&));

    MOCK_METHOD0(getMinimalWorkplaceOccupation, size_t());

    MOCK_METHOD1(getUsageTime, double(size_t));
};