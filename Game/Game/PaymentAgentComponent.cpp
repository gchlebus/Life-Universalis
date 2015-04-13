//
//  PaymentAgentComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 13.04.15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "PaymentAgentComponent.h"


PaymentAction::PaymentAction(std::string description, unsigned int cashAmount, PaymentAgentComponent *targetAgent)
{
    desc = description;
    amount = cashAmount;
    target = targetAgent;
    date = ((DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME))->getCurrentGameDate();
}

PaymentAgentComponent::PaymentAgentComponent() : GameObjectComponent("PaymentAgentComponent")
{
    
}

void PaymentAgentComponent::addPayment(PaymentAction *payment)
{
    _addedActions.push_back(payment);
}

