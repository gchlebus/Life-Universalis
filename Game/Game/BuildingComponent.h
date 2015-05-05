//
//  BuildingComponent.h
//  LifeUniversalis
//
//  Created by Pawel Sulik on 14.02.15.
//
//

#pragma once

#include <GameEngine.h>
#include "IMachine.h"

class PaymentAgentComponent;

class BuildingComponent
    : public GameObjectComponent
{
public:
    BuildingComponent();

    virtual ~BuildingComponent();

    virtual void onParentChangedComponents() override;

    virtual void onUpdate() override;

    // Currently takes ownership of the machine.
    void addMachine(IMachine* machine);

    Workplace::PtrVector getWorkplaces();

    PaymentAgentComponent* paymentAgent;

protected:
    bool _isMachinePresent(IMachine* machine);

    IMachine::PtrVector _machines;
};
