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
		first = new char(strlen(firstIn) + 1);
		strcpy(first,firstIn);
		last = new char(strlen(lastIn) + 1);
		strcpy(last,lastIn);
		id = idIn;
		gpaIn;
	}
	~student() {
		delete first;
		delete last;
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
	int tablelength;
	item* items[];
	hashT(int length) {
		item* items[length];
		tablelength = length;
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

void addStudent(hashT* &hash, student* sIn) {
	int slot = hashify(sIn, hash);
	cout << slot << endl;
	item* insert = hash->items[slot];
	if (insert == NULL) {
		hash->items[slot] = new item(sIn);
	}
	else {	
		while (insert->next != NULL) {
			insert = insert->next;
		}
		insert->next = new item(sIn);
	}
}
bool rehash(hashT* &hashIn) {
	bool re = false;
	for (int i = 0; i >= hashIn->tablelength; i++) {
		int col = 0;
		item* reader1 = hashIn->items[i];
		while (reader1 != NULL || reader1->next != NULL) {
			col++;
			cout << col << endl;
			if (col > 3) {
				re = true;
			}
			reader1 = reader1->next;
		}
	}
	if (!re) {
		return false;
	}
	hashT* newHash = new hashT(hashIn->tablelength * 2);
	for (int i = 0; i >= hashIn->tablelength; i++) {
		item* reader = hashIn->items[i];
		addStudent(newHash, reader->s);
		while (reader->next != NULL) {
			reader = reader->next;
			addStudent(newHash, reader->s);
		}
	}
	hashIn = newHash;
	return true;	
}
hashT* newHashTable(int size) {
	hashT* hashPointer = new hashT(size);
	for (int i=0; i<=size; i++) {
		hashPointer->items[i] = NULL;
	}
	return hashPointer;
}
int main() {	
	hashT* studentHash = newHashTable(100);
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
		while (reading <= 999) {
			char temp[20] = {'\0'};
			firstIndex = 0;
			while (true) {
				firstfile.get(ch);
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
		while (reading <= 999) {
			char temp[20] = {'\0'};
			lastIndex = 0;
			while (true) {
				lastfile.get(ch);	
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

			student* s = new student(sfname, slname, sid, sgpa);

			addStudent(studentHash, s);
			cout << studentHash->items[1]->s->first << endl;
			cout << studentHash->items[1]->next->s->first << endl;
			cout << studentHash->items[1]->next->next->s->first << endl;
			cout << studentHash->items[1]->next->next->next->s->first << endl;

		}
		else if (strcmp(input, "PRINT") == 0) { //print students
			//printStudent(students);
		}
		else if (strcmp(input, "DELETE") == 0) { //delete students
			//deleteStudent(students);
		}
		else if (strcmp(input, "QUIT") == 0) { //quit program
			return 0;
        	}
		while (rehash(studentHash)) {
			cout << "rehashed" << endl;
		}
	}
	return 0;
}
