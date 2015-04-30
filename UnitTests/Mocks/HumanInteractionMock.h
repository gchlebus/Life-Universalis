#pragma once

#include <gmock/gmock.h>
#include "HumanInteraction.h"

class HumanInteractionMock
    : public HumanInteraction
{
public:
    MOCK_METHOD0(getInteractionName, std::string());
    MOCK_METHOD0(onBeforeExecute, void());
    MOCK_METHOD0(onExecute, Result());
    MOCK_METHOD0(getTarget, Vector3());
    MOCK_METHOD0(getDistanceThreshold, float());
};
