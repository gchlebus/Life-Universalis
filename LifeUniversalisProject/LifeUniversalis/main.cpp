#include <iostream>
#include <cstdio>

#include "LifeUniversalis.h"

using namespace std;

int main()
{
	Human *human = new Human();
	cout << "Human stats:\n\tHunger: " << human->hunger
					<< "\n\tHealth: " << human->health
					<< "\n\tEntertainment: " << human->entertainment
					<< "\n\tEducation: " << human->education;

	system("pause");
	return 0;
}