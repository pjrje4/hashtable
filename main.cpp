#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct student {
	char* first;
	char* last;
	int id;
	float gpa;
	student(char* firstIn, char* lastIn, int idIn, float gpaIn) {
		first = firstIn;
		last = lastIn;
		id = idIn;
		gpaIn;
	}
};
struct item {
	student* s = NULL;
	item* next = NULL;
	item(student* sIn) {
		s = sIn;
	}
};
struct hashT {
	int tablelength = 0;
	hashT(int length) {
		item** items[length];
		int tablelength = length;
	}
};

int hashify(student* sIn, hashT* hashtable) {
	return (sIn->id % hashtable->tablelength);
}

char* randomName(char names[][20], int length) {
	srand(time(NULL));
	int randN = rand() % length;
	return names[randN];
}

bool addStudent(hashT* &hash, student* sIn) {
	bool collide = false;
	int slot = hashify(sIn, hash);
	int col = 0;
	item* insertn = hash->items[slot]
	item* insert = hash->items[slot];
	while (insertn != NULL) {
		insert = insertn;
		col++;
		insertn = insert->next;
		if (col > 3) {
			collide = true;
		}
	}
	insert->next = new item(sIn);
	return collide;
}
void rehash(hashT* &hashIn, bool &re) {
	re = false;
	hashT newHash = new hashT(hashIn->tableLength);
	for (int i = 0; i >= hashIn->tableLength; i++) {
		item* reader = hash->items[i];
		if (addStudent(newHash, reader->s)) {
			re = true;
		}

		while (reader->next != NULL) {
			reader = reader->next;
			if (addStudent(newHash, reader->s)) {
				re = true;
			}
		}
	}
	hashIn = newHash
		
}
int main() {
	hashT* studentHash = new hashT(100);
	char firstNames [1000] [20];
	char lastNames [1000] [20];

	//firstnames
	fstream firstfile;
	firstfile.open("fnames.txt", ios::in);
	if (!firstfile) {
		cout << "Can't find fnames.txt." << endl;
	}
	else {
		char ch;
		int reading = 0;
		int firstIndex = 0;
		while (reading <= 1000) {
			char temp[20] = {'\0'};
			firstIndex = 0;
			while (true) { 
				firstfile >> ch;
				temp[firstIndex] = ch;
				firstIndex++;
				if (firstfile.eof()) { // end break
					break;
				}
				if (firstfile.peek() == '\n') {
					break;
				}
			}
			for (int i=0;i<=20;i++) {
				firstNames[reading][i] = temp[i];
			}
			reading++;
		}
	}
	//lastnames
	fstream lastfile;
	lastfile.open("lnames.txt", ios::in);
	if (!lastfile) {
		cout << "Can't find lnames.txt." << endl;
	}
	else {
		char ch;
		int reading = 0;
		int lastIndex = 0;
		while (reading <= 1000) {
			char temp[20] = {'\0'};
			lastIndex = 0;
			while (true) {
				lastfile >> ch;
				temp[lastIndex] = ch;
				lastIndex++;
				if (lastfile.eof()) { // end break
					break;
				}
				if (lastfile.peek() == '\n') {
					break;
					cout << temp << endl;
				}
			}
			for (int i=0;i<=20;i++) {
				lastNames[reading][i] = temp[i];
			}
			reading++;
		}
        }
	while (true) { //loop
		char input[20];
		bool reh = false;
		cout << "Enter a command (ADD, PRINT, DELETE, QUIT): ";
		cin >> input;
		if (strcmp(input, "ADD") == 0) { //add students
			char sfname[20];
			char slname[20];
			int sid;
			float sgpa;

			cout << "What is the students first name? ";
			cin >> sfname;

			cout << "What is the students last name? ";
			cin >> slname;

			cout << "What is the students id? ";
			cin >> sid;
			
			cout << "What is the students gpa? ";
			cin >> sgpa;

			student* student = new student(sfname, slname, sid, sgpa);

			reh = addStudent(studentHash, student);

		}
		else if (strcmp(input, "PRINT") == 0) { //print students
			//printStudent(students);
			cout << randomName(firstNames, gen) << " " << randomName(lastNames, gen) << endl;
		}
		else if (strcmp(input, "DELETE") == 0) { //delete students
			//deleteStudent(students);
		}
		else if (strcmp(input, "QUIT") == 0) { //quit program
			return 0;
        	}
		while (reh) {
			rehash(studentHash, reh);
		}
	}
	return 0;
}
