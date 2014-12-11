#include <iostream>
#include <cstdio>

#include "LifeUniversalis.h"

using namespace std;

int main()
{
	Kernel::init();
	Human *human = new Human();
	cout << "Human stats:\n\tsatiety: " << human->satiety
					<< "\n\tHealth: " << human->health
					<< "\n\tEntertainment: " << human->entertainment
					<< "\n\tEducation: " << human->education;

	system("pause");
	return 0;
}