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

char* randomName(char names[][20], int length) {
	srand(time(NULL));
	int randN = rand() % length;
	return names[randN];
}

int main() {
	while (true) { //loop
		char input[20];
		int gen;
		cout << "How many students to generate (1-1000): ";
		cin >> gen;

		char firstNames [gen] [20];
		char lastNames [gen] [20];

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
			while (reading <= gen) {
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
                        while (reading <= gen) {
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
                                        }
                                }
                                for (int i=0;i<=20;i++) {
                                        lastNames[reading][i] = temp[i];
                                }
                                reading++;
                        }
                }

		cout << "Enter a command (ADD, PRINT, DELETE, QUIT): ";
		cin >> input;
		if (strcmp(input, "ADD") == 0) { //add students
			//addStudent(students);
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
	}
	return 0;
}
