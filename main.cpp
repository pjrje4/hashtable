#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct student {
	char* first;
	char* last;
	int id;
	float gpa;
	student(char* firstIn, char* lastIn) {
		first = firstIn;
		last = lastIn;
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

int main() {
	while (true) { //loop
		char input[20];
		int gen;
		cout << "How many students to generate (1-1000): ";
		cin >> gen;

		char firstNames [gen] [20];
		char lastNames [gen] [20];
		fstream firstfile;
		firstfile.open("fnames.txt", ios::in);
		if (!firstfile) {
			cout << "Can't find fnames.txt." << endl;
		}
		else {
			//char temp[20];
			//char tempC;
			char ch;
			while (true) {
				//tempC = 
				//while 
				firstfile >> ch;
				if (firstfile.eof()) {
					break;
				}
				cout << ch;
			}

		}

		cout << "Enter a command (ADD, PRINT, DELETE, QUIT): ";
		cin >> input;
		if (strcmp(input, "ADD") == 0) { //add students
			//addStudent(students);
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
	}
	return 0;
}
