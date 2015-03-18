//
//  ConsoleLogger.h
//  GameEngine
//
//  Created by Pawel Sulik on 18/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

<<<<<<< Updated upstream
#ifndef GameEngine_ConsoleLogger_h
#define GameEngine_ConsoleLogger_h


#endif
=======
#pragma once
#include "GlobalHeaders.h"
#include "ILogger.h"

class GAMEENGINE_EXPORT ConsoleLogger : public ILogger
{
public:
    void log(std::string txt, WarningLevel lvl, std::string filename, int lineNum);
protected:
};
>>>>>>> Stashed changes
