//
//  HumanWorkInteraction.h
//  Game
//
//  Created by Pawel Sulik on 31/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include "GlobalHeaders.h"
#include "HumanInteraction.h"

class HumanWorkInteraction : public HumanInteraction
{
public:
    
    std::string getInteractionName();
    
    void onExecute();
    void onUpdate();
    void onStop();
    void onForceAbort();
protected:
};
