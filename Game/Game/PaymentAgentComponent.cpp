//
//  PaymentAgentComponent.cpp
//  Game
//
//  Created by Pawel Sulik on 13.04.15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "PaymentAgentComponent.h"


PaymentAction::PaymentAction(std::string description, unsigned int cashAmount, PaymentAgentComponent *sourceAgent)
{
    desc = description;
    amount = cashAmount;
    source = sourceAgent;
    date = ((DayTimeEntity*)GameEngine::engine()->currentEnvironment->findEntity(EN_DAYTIME))->getCurrentGameDate();
}

PaymentAgentComponent::PaymentAgentComponent() : GameObjectComponent("PaymentAgentComponent")
{
    _cash = 1000;
}

PaymentResult PaymentAgentComponent::bookPayment(unsigned int amount, PaymentAgentComponent *target, std::string description)
{
    if(target == nullptr)
        return PaymentResult::InvalidTarget;
    if((int)amount >= _cash)
        return PaymentResult::InsufficientFinancialResources;
    PaymentAction *payment = new PaymentAction(description, amount, this);
    target->addPayment(payment);
    _cash -= amount;
    
    LOGF(F("💵Booked payment!\n💵\tSum: %1%,-\n💵\tDescription: %2%\n💵\tCurrent balance: %3%,-") % amount % description % _cash);
    
    return PaymentResult::OK;
}

void PaymentAgentComponent::addPayment(PaymentAction *payment)
{
    _addedPayments.push_back(payment);
}

void PaymentAgentComponent::onUpdate()
{
    while(_addedPayments.size())
    {
        PaymentAction *currentAction = _addedPayments.front();
        
        _cash += currentAction->amount;
        _history.push_back(currentAction);
        _addedPayments.pop_front();
        
        LOGF(F("💵Realized payment!\n💵\tSum: %1%,-\n💵\tDescription: %2%\n💵\tCurrent balance: %3%,-") % currentAction->amount % currentAction->desc % _cash);
    }
}