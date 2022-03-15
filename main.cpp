#include <iostream>
#include <list>
#include <cstring>

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
		gpa = gpaIn;
	}
	~student() {
		delete first;
		delete last;
	}
};

class HashTable {
private:
	int numElements;
	// Hash function to calculate hash for a value:
	int hashify(int input) {
		return input % numElements;
	}
public:
	student** table;
	// Constructor to create a hash table with 'n' indices:
	HashTable(int n) {
		table = new student*[n];
		numElements = n;
		for(int i = 0; i < numElements; i++){
			table[i] = nullptr;
		}
	}

	// Insert data in the hash table:
	int addStudent(student* s) {
		int col = 0;
		int x = hashify(s->id);
		while (table[x] != NULL) {
			if (x == numElements-1) {
				col = 4;
			}
			x++;
			col++;
		}
		table[x] = s;
		return col;
	}

	// Remove data from the hash table:
	void deleteStudent(int id){
		int x = hashify(id);
		for (int i = 0; i < 5; i++) {
			if (table[x + i]->id == id) {
				table[x+i] = NULL;
				cout << "Deleted ID " << id <<  endl;
				return;
			}
		}
		cout << "Couldn't find student with ID " << id << endl;
	}

	void print(){
		// Traverse each index:
		for(int i = 0; i < numElements; i++){
			if (table[i] != NULL) {
				cout << i << ": " << table[i]->first  << " " << table[i]->last << " " << table[i]->id << " " << table[i]->gpa << endl; 
			}
		}
	}
	HashTable* rehash() {
		bool re = true;
		HashTable* htnew;
		while (re) {
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
};

int main() {
	// Create a hash table with 100 indices:
	HashTable* ht = new HashTable(100);
	while (true) { //loop
		char input[20];
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

			if (ht->addStudent(s) > 3) {
				ht = ht->rehash();
			}

		}
		else if (strcmp(input, "PRINT") == 0) { //print students
			//printStudent(students);
			ht->print();
		}
		else if (strcmp(input, "DELETE") == 0) { //delete students
			//deleteStudent(students);
			int delId;
			cout << "What is the student's ID that you want to delete?  ";
			cin >> delId;
			ht->deleteStudent(delId);

		}
		else if (strcmp(input, "QUIT") == 0) { //quit program
			return 0;
        	}
	}
	return 0;
}
