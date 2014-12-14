#include <iostream>
#include <cstdio>

#include "LifeUniversalis.h"

using namespace std;

int main()
{
	Human *human = new Human();
	cout << "Human stats:\n\tsatiety: " << human->getSatiety()
					<< "\n\tHealth: " << human->getHealth()
					<< "\n\tEntertainment: " << human->getEntertainment()
					<< "\n\tEducation: " << human->getEducation();

	system("pause");
	return 0;
}