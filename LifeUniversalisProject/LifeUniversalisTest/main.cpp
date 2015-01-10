#include <gtest\gtest.h>
#include "../LifeUniversalis/LifeUniversalis.h"
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Kernel *gKernel;

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	gKernel = new Kernel();
	gKernel->timer->tick();

	for(int i = 0; i < 15; i++)
	{
		_sleep(100);
		gKernel->timer->tick();
		cout << "Current delta: " << gKernel->timer->getLastDelta() << "\n";
	}

	return RUN_ALL_TESTS();
}