//
//  ConsoleLogger.h
//  GameEngine
//
//  Created by Pawel Sulik on 18/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#pragma once
#include "GlobalHeaders.h"
#include "ILogger.h"

class GAMEENGINE_EXPORT ConsoleLogger : public ILogger
{
public:
    void log(std::string txt, WarningLevel lvl, std::string filename, int lineNum);
protected:
};
