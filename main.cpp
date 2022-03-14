#include <iostream>
#include <list>
#include <cstring>

using namespace std;

struct student {
	char* first;
	char* last;
	int id;
	float gpa;
	student(){};
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
	student* table[];
	// Constructor to create a hash table with 'n' indices:
	HashTable(int n) {
		numElements = n;
		student* table[n];
		for(int i = 0; i < numElements; i++){
			table[i] = nullptr;
		}
	}

	// Insert data in the hash table:
	int insertElement(student* key) {
		int col = 0;
		int x = hashify(key->id);
		cout << table[x] << endl;
		while (table[x] != NULL) {
			cout << x << " not null" << endl;
			x++;
			col++;
		}
		table[x] = key;
		return col;
	}

	// Remove data from the hash table:
	void removeElement(student* key){
		int x = hashify(key->id);
		for (int i = 0; i < 3; i++) {
			if (table[x + i]->id == key->id) {
				table[x+i] = NULL;
			}
		}
	}

	void printAll(){
		// Traverse each index:
		for(int i = 0; i < numElements; i++){
			cout << "Index " << i << ": " << table[i]->first << endl; 
		}
	}
	HashTable* rehash() {
		bool re = false;
		HashTable* htnew = new HashTable(numElements * 2);
		for(int i = 0; i < numElements; i++){
			if (table[i] != NULL) {
				if (htnew->insertElement(table[i]) > 3) {
					re = true;
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

			cout << ht->insertElement(s) << endl;

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
