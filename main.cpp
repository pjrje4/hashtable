#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip> 

/*
 *Justin Iness
 *11/17/2021
 *Student List
 * C++ Programming
 */

using namespace std;
struct Student { //student struct
	char firstName[20];
	char lastName[20];
	int id;
	float gpa;
};
void addStudent(vector<Student*>*);
void printStudent(vector<Student*>*);
void deleteStudent(vector<Student*>*);

int main() {
	vector<Student*>* students = new vector<Student*>();
	while (true) { //loop
		char input[20];
		cout << "Enter a command (ADD, PRINT, DELETE, QUIT): ";
		cin >> input;
		if (strcmp(input, "ADD") == 0) { //add students
			addStudent(students);
		}
		else if (strcmp(input, "PRINT") == 0) { //print students
			printStudent(students);
		}
		else if (strcmp(input, "DELETE") == 0) { //delete students
			deleteStudent(students);
		}
		else if (strcmp(input, "QUIT") == 0) { //quit program
			return 0;
        	}
	}
}
