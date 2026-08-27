#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std; 

void addSubjects(); 
void checkHeader(); // This function checks if it should add the header "Subject Code, Grade, Unit" or not.
void makeFile(string newFileName); 
double calcGWA(); // This function just calculates the GWA.
void addGWA();
void deleteFile();
void displayGrades(); /* This function:
							asks for the Year and Semester, after which the grades will be displayed.
							Only the latter has been implemented so far;
					  */ 

void addYear();

int main(int argc, char** argv) {
	int mainOp; 
	do {
		cout << "1. Add (Year/Sem/Grades)\n";
		cout << "2. Edit Grades\n";
		cout << "3. Display Grades\n";
		cout << "4. Remove (Year/Sem/Grades)\n";
		cout << "5. Exit\n";
		cout << "Choose an option: ";
		cin >> mainOp; 
		switch(mainOp) {
			case 1: 
				int firstOp;
				std::cout << "1. Add Year\n";
				std::cout << "2. Add Semester\n";
				std::cout << "3. Add Grades\n";
				std::cout << "4. Exit\n";
				std::cout << "Choose an option: ";
				std::cin >> firstOp;
				switch(firstOp){
					case 1: 
						addYear(); 
						break;  
					case 4:
						return 0;
				}
				break;
//				addSubjects();
//				break;
			case 2: 
			break;
//				string newFileName; 
//				cout << "What is the name of this grade folder? (Please, do not use spaces): "; 
//				cin >> newFileName; 
//				newFileName += ".csv"; 
//				makeFile(newFileName); 
//				break;
			case 3:
				displayGrades();
				break;
			case 4:
				deleteFile();
				break;
			case 5:
				break;
		}
	} while(mainOp != 3); 
	calcGWA();
	return 0;
}

void addYear() {
	cout << "Input year: ";  
	int year; 
	cin >> year; 
	cout << "Added " << year; 
	if(year % 10 == 1) {
		cout << "st "; 
	} else if (year % 10 == 2) {
		cout << "nd "; 
	} else if (year % 10 == 3) {
		cout << "rd "; 
	} else {
		cout << "th ";
	}
	
	cout << "year folder.\n\n";
	return; 
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

void makeFile(string newFileName) {
	ofstream file; 
	file.open(newFileName.c_str()); 
	if(file.is_open()) {
		cout << "\nFile has been made succesfully!\n\n"; 
		file.close();
		return;
	}
}

double calcGWA(){
	fstream f;
	string l = "";
	int location = 0;
	double ret = 0, unitTotal = 0;
	
//	f.open("grades.csv", ios::in);
//	while(getline(f,l)){
//		location = l.find(',');
//		string tmp = l.substr(0,location);
//		l = l.substr(location + 1, l.length());
//		location = l.find(',');
//		double grade = std::stod(l.substr(0,location));
//		l = l.substr(location + 1, l.length());
//		double unit = std::stod(l);
//		ret += grade * unit;
//		unitTotal += unit;
////		std::cout << tmp << ": " << grade << ", " << unit << endl;
//	}
//	
//	std::printf("GWA: %.3f", ret / unitTotal); // debugging purposes
	return ret / unitTotal;
}

void displayGrades(){
	fstream f;
	string l;
	int location = 0;
	f.open("grades.csv", ios::in);
	std::cout << std::endl;
	while(getline(f,l)){
		std::cout << "|\t";
		location = l.find(',');
		string tmp = l.substr(0,location);
		std::cout << tmp;
		if(tmp.length() >= 9) std::cout << "\t|\t";
		else std::cout << "\t\t|\t";
		l = l.substr(location + 1, l.length());
		location = l.find(',');
		tmp = l.substr(0,location);
		double d = std::stod(tmp);
		std::printf("%.1f", d);
		std::cout << "\t|\t";
		l = l.substr(location + 1, l.length());
		tmp = l;
		d = std::stod(tmp);
		std::printf("%.1f", d);
		std::cout << "\t|\n";
//		std::cout << tmp << ": " << grade << ", " << unit << endl;
	}
}



