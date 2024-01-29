#pragma once
#include <memory>
class Family
{
public:
	int numFamily;
	char FamilyName [20];
	int peopleNumOfFamily;
	long phone;//0504119712--------------?????????????
	bool IsClasses[6];
	Family() {
		this->numFamily = 0;

		this->peopleNumOfFamily = 0;
		this->phone = 0;
		strcpy_s(this->FamilyName, "                   ");

		for (size_t i = 0; i < 6; i++)
		{
			this->IsClasses[i] = false;
		}
	}
};

