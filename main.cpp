#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#if 0
Justin Iness
3/15/2022
C++ Programming
HashTable
#endif

using namespace std;

struct student { // Student Object
	char* first;
	char* last;
	int id;
	float gpa;
	student(char* firstIn, char* lastIn, int idIn, float gpaIn) { // Parametized Constructor
		first = new char(strlen(firstIn) + 1);
		strcpy(first,firstIn);
		last = new char(strlen(lastIn) + 1);
		strcpy(last,lastIn);
		id = idIn;
		gpa = gpaIn;
	}
	~student() { // Destructor because we used new
		delete first;
		delete last;
	}
};

class HashTable {
private:
	int numElements;
	int used;
	// Hash function
	int hashify(int input) {
		return input % numElements;
	}
public:
	student** table; // Store Student Pointers in an Array
	// Parametized Constructor to make an array of length n
	HashTable(int n) {
		table = new student*[n];
		numElements = n;
		used = 0;
		for(int i = 0; i < numElements; i++){ // Empty table
			table[i] = nullptr;
		}
	}

	// Add a student
	int addStudent(student* s) {
		int col = 0;
		int x = hashify(s->id);
		while (table[x] != NULL) {
			if (x == numElements-1) { // If end of array resize to be bigger
				col = 4;
				cout << "ID too large: doubling array size" << endl;
			}
			x++;
			col++;
		}
		table[x] = s;
		used++;
		return col; // How many Collisions?
	}

	// Delete Student
	void deleteStudent(int id) {
		int x = hashify(id);
		for (int i = 0; i < 5; i++) {
			if (table[x + i]->id == id) {
				delete table[x+i];
				table[x+i] = NULL;
				cout << "Deleted ID " << id <<  endl;
				return;
			}
		}
		cout << "Couldn't find student with ID " << id << endl;
	}

	void print() { // Print Entire Table
		for(int i = 0; i < numElements; i++){
			if (table[i] != NULL) {
				cout << i << ": " << table[i]->first  << " " << table[i]->last << " " << table[i]->id << " " << table[i]->gpa << endl; 
			}
		}
	}
	HashTable* rehash() { // Return HashTable that has its size doubled and rehashed
		bool re = true;
		HashTable* htnew;
		while (re) { // Rehash until less then 3 collisions
			re = false;
			htnew = new HashTable(numElements * 2);
			for(int i = 0; i < numElements; i++){
				if (table[i] != NULL) {
					if (htnew->addStudent(table[i]) > 3) {
						re = true;
					}
				}
			}
		}
		return htnew;
	}
	int length() { // Return number of elements
		return used;
	}
	int total() { // Return max elements (array size)
		return numElements;
	}
};

char* randomName(char names[][20]) { // Generate a random name
	int randN = rand() % 1000;
	return names[randN];
}
float rGPA() { // Generate a random GPA
	float randomGPA = float((rand() % 300)) / 100 + 1;
	return randomGPA;
}

int main() {
	char firstNames [1000] [20]; // Store first and lasts
	char lastNames [1000] [20];

	srand(time(NULL));

	// Firstnames
        fstream firstfile;
        firstfile.open("fnames.txt", ios::in);
        if (!firstfile) {
                cout << "Can't find fnames.txt." << endl;
        }
        else { // File exists
                int reading = 0;
                while (reading <= 1000) {
                        if (firstfile.eof()) { // End break
                                break;
                        }
                        char temp[20] = {'\0'}; // emty
                        firstfile.getline(temp, 20);
                        for (int i=0;i<20;i++) {
                                firstNames[reading][i] = temp[i];
                        }
                        reading++;
                }

        }
	firstfile.close();
	//lastnames
	fstream lastfile;
	lastfile.open("lnames.txt", ios::in);
	if (!lastfile) {
		cout << "Can't find lnames.txt." << endl;
	}
	else {
		int reading = 0;
		while (reading <= 1000) {
			if (lastfile.eof()) { // End break
				break;
			}
			char temp[20] = {'\0'};
			lastfile.getline(temp, 20);
			for (int i=0;i<20;i++) {
				lastNames[reading][i] = temp[i];
			}
			reading++;
		}

        }
	lastfile.close();
	// New hash of size 100
	HashTable* ht = new HashTable(100);
	while (true) { // Loop
		char input[20];
		cout << "Enter a command (ADD, PRINT, DELETE, GEN, QUIT): ";
		cin >> input;
		if (strcmp(input, "ADD") == 0) { // Add students
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

			student* s = new student(sfname, slname, sid, sgpa); // New student from input

			if (ht->addStudent(s) > 3) { // If more then 3 collisions rehash
				ht = ht->rehash();
			}
			if (ht->length() > ht->total()/2) { // Rehash if over half full
				ht = ht->rehash();
			}	

		}
		else if (strcmp(input, "PRINT") == 0) { // Print students
			ht->print();
		}
		else if (strcmp(input, "DELETE") == 0) { // Delete students
			int delId;
			cout << "What is the student's ID that you want to delete?  ";
			cin >> delId;
			ht->deleteStudent(delId);

		}
		else if (strcmp(input, "GEN") == 0) { // Generate random students
			int genNum;
			cout << "How many students would you like to generate?  ";
			cin >> genNum;
			for (int i = 0; i < genNum; i++) {
				// Generate Random Student
				student* s = new student(randomName(firstNames), randomName(lastNames), ht->length(), rGPA());
				ht->addStudent(s);
				if (ht->length() > ht->total()/2) { // Rehash if over half full
					ht = ht->rehash();
				}	
			}

        	}
		else if (strcmp(input, "QUIT") == 0) { // Quit program
                        return 0;
                }

	}
	return 0;
}
