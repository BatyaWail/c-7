#include "Family.h"
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;
bool isCurseAvilable(fstream& file, int idCurse) {
	Family family;
	int count = 0;

	for (int i = 0; i < 100; i++)
	{
		file.seekg(0, sizeof(Family));
		file.read((char*)&family, sizeof(Family));
		if (family.IsClasses[idCurse] == true)
			count++;
	}
	if (count < 10)
		return true;
	return false;
}
bool isTheFamilyExist(fstream& file, int numFamily) {
	if (numFamily < 1 || numFamily>100) {
		throw "ERROR: invalid family number";
		return false;
	}
	//fstream file(url, ios::binary);
	Family exitingFamily;
	file.seekg((numFamily - 1) * sizeof(Family), ios::beg);
	file.read((char*)&exitingFamily, sizeof(Family));
	if (exitingFamily.numFamily == 0) {
		throw "ERROR: Family is not on the file";
		return false;
	}
}
void setFile(fstream& file) {
	//fstream file(url, ios::binary);
	Family f1;
	for (int i = 0; i < 100; i++)
	{
		file.write((char*)&f1, sizeof(Family));
	}
	//file.close();
}
void add(fstream& file) {
	Family family;
	//fstream file(url, ios::binary);
	int numFamily, peopleNumOfFamily;
	char FamilyName[20], phone[10];
	cout << "enter numFamily" << endl;
	cin >> numFamily;
	if (numFamily < 1 || numFamily>100) {
		throw "ERROR: invalid family number";
		return;
	}
	file.seekg((numFamily - 1) * sizeof(Family), ios::beg);
	file.read((char*)&family, sizeof(Family));
	if (family.numFamily != 0) {
		throw "ERROR: family is already in the file";
		return;
	}
	family.numFamily = numFamily;
	cout << "enter family name" << endl;
	cin >> family.FamilyName;
	cout << "enter phone" << endl;
	cin >> family.phone;
	cout << "enter number of people on the family" << endl;
	cin >> family.peopleNumOfFamily;
	file.seekp((numFamily - 1) * sizeof(Family), ios::beg);
	file.write((char*)&family, sizeof(Family));
}
void del(fstream& file, int numFamily) {
	if (numFamily < 1 || numFamily>100) {
		throw "ERROR: invalid family number";
		return;
	}

	//fstream file(url, ios::binary);
	Family family;

	file.seekp((numFamily - 1) * sizeof(Family), ios::beg);
	file.write((char*)&family, sizeof(Family));
}
//void update(fstream& file, int numFamily) {
//	if (numFamily < 1 || numFamily>100) {
//		throw "ERROR: invalid family number";
//		return;
//	}
//	//fstream file(url, ios::binary);
//	Family exitingFamily, tempFamily;
//	file.seekg((numFamily - 1) * sizeof(Family), ios::beg);
//	file.read((char*)&exitingFamily, sizeof(Family));
//	if (exitingFamily.numFamily == 0) {
//		throw "ERROR: Family is not on the file";
//		return;
//	}
//	bool flag;
//	char temp = ' ';
//	int count = 0;
//	queue<Family>q1;
//
//	for (int i = 0; i < 6; i++)
//	{
//		count = 0;
//		cout << "do you want to register to chug number: " << i << " ? (Y/N)" << endl;
//		cin >> temp;
//		if (temp == 'Y') {
//			/*for (int i = 0; i < 100; i++)
//			{
//				file.read((char*)&tempFamily, sizeof(Family));
//				if (tempFamily.IsClasses[i])
//					count++;
//			}
//			if (count < 10) {
//				exitingFamily.IsClasses[i] = true;
//			}*/
//			if (isCurseAvilable(file, i))
//				exitingFamily.IsClasses[i] = true;
//			else {
//				for (int j = 0; j < 6; j++)
//				{
//					exitingFamily.IsClasses[j] = false;
//				}
//				exitingFamily.IsClasses[i] = true;
//				q1.push(exitingFamily);//??????????? האים התור אמור להיות מסודר לפי חוגים
//			}
//		}
//	}
//	file.seekp((numFamily - 1) * sizeof(Family), ios::beg);
//	file.write((char*)&exitingFamily, sizeof(Family));
//
//}
void update(std::fstream& file, int index, std::queue<Family>& waitingQueue) {
	if (index < 1 || index > 100) {
		throw "ERROR: Invalid family number";
	}
	file.seekp((index - 1) * sizeof(Family));

	Family existingFamily;
	file.read((char*)&existingFamily, sizeof(Family));
	if (existingFamily.numFamily == 0) {
		throw "ERROR: Family is not in the file";
	}

	bool clubs[6];

	for (int i = 0; i < 6; i++) {
		cout << "Enter true/false (1/0) for club number:  " << i + 1 << endl;
		cin >> clubs[i];
	}
	bool flug = false;
	for (int i = 0; i < 6; i++) {
		int countOnClub = 0;
		if (clubs[i]) {
			file.seekg(0, std::ios::beg); // Reset file position to the beginning
			Family f;
			for (int j = 0; j < 100; j++) {
				file.read((char*)&f, sizeof(Family));
				if (f.numFamily != 0) {
					if (f.IsClasses[i] == true)
						countOnClub++;
				}
			}
			if (countOnClub < 10) {
				existingFamily.IsClasses[i] = true;
				clubs[i] = false;
			}
			else {

				cout << "there is more then 10 to club number: " << i << endl;
				existingFamily.IsClasses[i] = false;
				flug = true;
			}
		}
	}

	file.seekp((index - 1) * sizeof(Family));
	file.write((char*)&existingFamily, sizeof(Family));
	if (flug)//ישנו חוג שהמשפחה לא הצליחה להכנס אליו...
	{
		for (int i = 0; i < 6; i++)
		{
			existingFamily.IsClasses[i] = clubs[i];
		}
		waitingQueue.push(existingFamily);
	}
}
void waiting(fstream& file, queue<Family>& q1) {
	//??????????????? איך עושים את זה????
	Family family, temp;
	char flag = ' ';
	while (!q1.empty()) {
		family = q1.front();
		if (isTheFamilyExist(file, family.numFamily) != false) {
			return;
		}
		for (int i = 0; i < 6; i++)
		{
			if (family.IsClasses[i] == true) {
				if (isCurseAvilable(file, i)) {
					cout << "do you realy want to register to curse number: " + i << "? (Y/N)" << endl;
					if (flag == 'Y') {
						file.seekg((family.numFamily - 1) * sizeof(Family), ios::beg);

						file.read((char*)&temp, sizeof(Family));
						temp.IsClasses[i] = true;
						file.seekp((family.numFamily - 1) * sizeof(Family), ios::beg);
						file.write((char*)&temp, sizeof(Family));

						//file.read((char*)&exitingFamily, sizeof(Family));
					}


				}
				else
					q1.push(family);
			}
		}
	}
}
bool rishum(fstream& file, int numFamily, int numCurse) {
	Family exitingFamily;
	if (isTheFamilyExist(file, numFamily))
		return true;
	if (exitingFamily.IsClasses[numCurse] == false) {
		throw "ERROR: invalid family number";
	}
	return true;
}
void print(fstream& file, int numOfFamily)
{
	if (!isTheFamilyExist(file, numOfFamily))
		return;
	int id;
	file.seekg((numOfFamily - 1) * sizeof(Family), ios::beg);
	file.read((char*)&id, sizeof(int));
	if (id == 0)
		throw "ERROR: family is not in file";
	Family family;
	file.seekg((numOfFamily - 1) * sizeof(Family), ios::beg);
	file.read((char*)&family, sizeof(Family));
	cout << "num family: " << family.numFamily << endl << "family name: " << family.FamilyName << "\n"
		<< "num of persons: " << family.peopleNumOfFamily << endl << "phone: " << family.phone << "\n";
	for (int i = 0; i < 6; i++)
	{
		if (family.IsClasses[i])
			cout << "class" << i << ": Y ";
		else
			cout << "class" << i << ": N ";
	}
	cout << endl;
}
void inClass(fstream& file, int numCurse) {
	if (numCurse < 1 || numCurse>6) {
		throw "ERROR: invalid class number!";
		return;
	}
	//fstream file(url, ios::binary);
	Family exitingFamily;
	file.seekg(0, ios::beg);
	for (int i = 0; i < 100; i++)
	{
		file.read((char*)&exitingFamily, sizeof(Family));
		if (exitingFamily.IsClasses[numCurse])
			cout << "the family name that registered to chug number " << i << " is: " << exitingFamily.FamilyName << endl;
	}
}
enum option
{
	EXIT,
	ADD,
	DEL,
	UPDATE,
	WAITING,
	RISHUM,
	PRINT,
	CLASS
};
int main()
{
	queue<Family> q;
	fstream file;
	file.open("families.txt", ios::binary | ios::in | ios::out);
	if (!file)
	{
		cout << "ERROR: couldn't open file\n";
		return 0;
	}
	setFile(file);
	int choice;
	int snum;
	int cnum;
	cout << "Choices are:\n0 to exit\n1 to add a family\n2 to delete a family\n3 to update rishum to classes\n4 to update waiting to classes \n5 to check rishum for a classas\n6 to print a family\n7 to print all the families that participate in a specific class\n";
	cout << "enter 0-7:\n";
	cin >> choice;
	while (choice)
	{
		switch (choice)
		{
		case ADD://add to the file
			try { add(file); }
			catch (const char* msg) { cout << msg; }
			break;
		case DEL://delete from file
			cout << "enter number of family to delete:\n";
			cin >> snum;
			try { del(file, snum); }
			catch (const char* msg) { cout << msg; }
			break;
		case UPDATE://update the list of classes of a family
			cout << "enter number of family to update:\n";
			cin >> snum;
			try { update(file, snum,q); }
			catch (const char* msg) { cout << msg; }
			break;
		case WAITING://update the list of classes of a waiting family
			waiting(file, q);
			break;
		case RISHUM://check rishum to a specific class
			cout << "enter number of family to check rishum:\n";
			cin >> snum;
			cout << "enter number of class to check rishum:\n";
			cin >> cnum;
			try
			{
				cout << "The family is" << (rishum(file, snum, cnum) ? " " : " not ") << "taking the class\n";
			}
			catch (const char* msg) { cout << msg; }
			break;
		case PRINT://print the details of a specific family
			cout << "enter number of family to print:\n";
			cin >> snum;
			try { print(file, snum); }
			catch (const char* msg) { cout << msg; }
			break;
		case CLASS://print the details of all the families that are taking a specific class
			cout << "enter number of class to check rishum:\n";
			cin >> cnum;
			try { inClass(file, cnum); }
			catch (const char* msg) { cout << msg; }
			break;
		default:
			cout << "ERROR: invalid choice\n";
		}
		cout << "\nenter 0-7:\n";
		cin >> choice;
	}
	file.close();
	return 0;
}




