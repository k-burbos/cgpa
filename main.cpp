#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

void addSubjects(); 
void checkHeader(); // This function checks if it should add the header "Subject Code, Grade, Unit" or not.
void makeFolder(string newFolderName); 
double calcGWA(); // This function just calculates the GWA.

int main(int argc, char** argv) {
	int answer; 
	do {
		cout << "What do you want to do?\n1. Add Subjects\n2. Make New Grade Folder\n3. Exit\nAnswer: "; 
		cin >> answer; 
		switch(answer) {
			case 1: 
				addSubjects();
				break;
			case 2: 
				string newFolderName; 
				cout << "What is the name of this grade folder? "; 
				cin >> newFolderName; 
				newFolderName += ".csv"; 
				makeFolder(newFolderName); 
				break;
		}
	} while(answer != 3); 
	calcGWA();
	return 0;
}

void addSubjects() {
	cout << "\n\n---------------------------------------------------------\n"; 
	cout << "Use \'&\' if you are finished inputting your grades.\n";
	char decision = '*'; 
	int totalSubjects;
	fstream myFile; 
	myFile.open("grades.csv", ios::app); 
	if(myFile.is_open()) {
		do {
			string subject; 
			double grade; 
			double unit; 
			cout << "\nSubject Code: ";
			cin >> subject; 
			cout << "Grade: "; 
			cin >> grade; 
			cout << "Unit for the subject: "; 
			cin >> unit; 
			cout << "Subject Added!\n\n"; 
			totalSubjects++; 
			cout << "Are you done? Input \'&\' if you are, \'*\' if not: ";
			cin >> decision; 
			myFile << subject << "," << grade << "," << unit << "\n"; 
		} while (decision != '&');
	
	}
 	
	cout << "\n\nYou have added " << totalSubjects << " subjects!"; 
}

void makeFolder(string newFolderName) {
	ofstream file; 
	file.open(newFolderName.c_str()); 
	if(file.is_open()) {
		cout << "Folder has been made succesfully!"; 
	}
}

double calcGWA(){
	fstream f;
	string l = "";
	int location = 0;
	double ret = 0, unitTotal = 0;
	
	f.open("grades.csv", ios::in);
	while(getline(f,l)){
		location = l.find(',');
		string tmp = l.substr(0,location);
		l = l.substr(location + 1, l.length());
		location = l.find(',');
		double grade = std::stod(l.substr(0,location));
		l = l.substr(location + 1, l.length());
		double unit = std::stod(l);
		ret += grade * unit;
		unitTotal += unit;
		std::cout << tmp << ": " << grade << ", " << unit << endl;
	}
	
	std::cout << ret / unitTotal; // debugging purposes
	return ret / unitTotal;
}




