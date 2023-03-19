#include<iostream>
#include<string.h>

using namespace std;

class Worker {
	private:
		int num;
		char *name;
		char *position;
		float workHour;
		
		static int* numWorkers;
	public:
		Worker();
		Worker(int, char*, char*, float);
		~Worker();
		
		void setNum(int);
		void setName(char*);
		void setPosition(char*);
		void setWorkHour(float);
		
		char* getName();
		char* getPosition();
		float getWorkHour();
		int getNum();
		

};

int* Worker::numWorkers = new int[1] {0};

Worker::Worker() {
	num = 3;
	name = new char[1]; strcpy(name, "");
	position = new char[6]; strcpy(position, "worker");
	workHour = 0;
}
Worker::Worker(int num, char* name, char* position, float workHour) {
	//check workHour
	if(!(workHour >= 0 && workHour <= 160)) {
		cout << "Error: Work hour must be more than 0, less than 160.";
		return;
	}
	
	//check duplicate
	for(int i = 1; i <= numWorkers[0]; i++) {
		if(num == numWorkers[i]) {
			cout << "Error: A worker with the same num (" << num << ") already exists." << endl;
			return;
		}
	}
	// If not, add to the numWorkers.
	int* newNumWorkers = new int[numWorkers[0] + 2];//!
	newNumWorkers[0] = numWorkers[0] + 1;
	for(int i = 1; i <= numWorkers[0]; i++) {
		newNumWorkers[i] = numWorkers[i];
	}
	newNumWorkers[numWorkers[0] + 1] = num;
	delete numWorkers;
	numWorkers = newNumWorkers;
	
	this->num = num;
	this->workHour = workHour;
	this->position = new char[strlen(position) + 1];
	strcpy(this->position, position);
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
Worker::~Worker() {
	//delete from the numWorkers
	int* newWorkers = new int[numWorkers[0]]; // !
	newWorkers[0] = numWorkers[0] - 1;
	int j = 1;
	for(int i = 1; i <= numWorkers[0]; i++) {
		if(numWorkers[i] != this->num) {
			newWorkers[j] = numWorkers[i];
			j++;			
		}
	}
	delete numWorkers;
	numWorkers = newWorkers;
	
	delete position;
	delete name;
	cout << "Deleted a worker. Num=" << num
		 << " name=" << name << " position=" 
		 << position << endl; 
}

char* Worker::getName() {
	return name;
}
char* Worker::getPosition() {
	return position;
}
float Worker::getWorkHour() {
	return workHour;
}
int Worker::getNum() {
	return num;
}

void Worker::setName(char* name) {
	delete this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);	
}
void Worker::setNum(int num) {
	if(num <= 0) {
		cout<<"err: Num must be more than 0.";	
		return;
	}
	
	//check if duplicate
	for(int i = 1; i <= numWorkers[0]; i++) {
		if(num == numWorkers[i]) {
			cout << "Error: A worker with the same num (" << num << ") already exists." << endl;
			return;
		}
	}
	
	this->num = num;
	
	//replace the old num with new num
	for(int i = 1; i <= numWorkers[0]; i++) {
		if(this->num == numWorkers[i]) {
			numWorkers[i] = num;
			break;
		}
	}
}
void Worker::setPosition(char* position) {
	delete this->position;
	this->position = new char[strlen(position) + 1];
	strcpy(this->position, position);
}
void Worker::setWorkHour(float workHour) {
	if(workHour >= 0 && workHour <= 160)
		this->workHour = workHour;
	else 
		cout<<"Error: Work hour must be more than 0, less than 160.";
}

int main() {
	int n, num;
	float workHour;
	char name[100], position[20];
	cin >> n;
	Worker workers[n];
	for(int i = 0; i < n; i++) {
		cout << "name: ";
		cin >> name;
		cout << "num: ";
		cin >> num;
		cout << "position: ";
		cin >> position;
		cout << "workhour: ";
		cin >> workHour;
		workers[i] = Worker(num, name, position, workHour);
	}
	
	cout << "Before sorting by name:" << endl;
	for(int i = 0; i < n; i++) {
		cout << "name: " << workers[i].getName();
		cout << "num: " << workers[i].getNum();
		cout << "position: " << workers[i].getPosition();
		cout << "workhour: " << workers[i].getWorkHour();
	}
	
	Worker temp;
	for(int i = 0; i < n; i++) {
		for(int j = 0; i < n - i - 1; j++) {
			if(strcmp(workers[i].getName(), workers[i + 1].getName()) > 0) {
				temp = workers[i];
				workers[i] = workers[i + 1];
				workers[i + 1] = temp;
			}
		}
	}
	
	cout << endl << "After sorting by name;" << endl;
	for(int i = 0; i < n; i++) {
		cout << "name: " << workers[i].getName();
		cout << "num: " << workers[i].getNum();
		cout << "position: " << workers[i].getPosition();
		cout << "workhour: " << workers[i].getWorkHour();
	}
}
