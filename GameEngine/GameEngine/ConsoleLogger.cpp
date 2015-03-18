//
//  ConsoleLogger.cpp
//  GameEngine
//
//  Created by Pawel Sulik on 18/03/15.
//  Copyright (c) 2015 LifeUniversalis. All rights reserved.
//

#include "ConsoleLogger.h"



void ConsoleLogger::log(std::string txt, WarningLevel lvl, std::string filename, int lineNum)
{
#ifndef GREGOR_TEST
    if(lvl >= _filter)
        std::cout << txt << "\n";
#endif
}
