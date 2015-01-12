#include <gtest\gtest.h>
#include "../LifeUniversalis/LifeUniversalis.h"
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
	GameEngine::engine()->run();
	GameEngine::engine()->tempJoin();
	::testing::InitGoogleTest(&argc, argv);


	return RUN_ALL_TESTS();
}