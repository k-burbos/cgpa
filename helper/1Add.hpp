#pragma once

#include "helperMain.hpp"


// FUNCTION DECLARATIONS
void caseOneMain();
void addSubjects();
void addGWA();
void checkHeader(); // This function checks if it should add the header "Subject Code, Grade, Unit" or not.
void makeFile(string newFileName);
void addYear();		// Adds years into Year Folder;
void addSemester(); // Adds semesters into year folders;
boolean directoryExists(string& name);



// FUNCTION DEFINITIONS
void caseOneMain(){
    int firstOp;
    do{
        std::cout << "1. Add Year\n";
        std::cout << "2. Add Semester\n";
        std::cout << "3. Add Grades\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> firstOp;
        switch (firstOp)
        {
            case 1:
                addYear();
                break;
            case 2:
                addSemester();
                break;
            case 3:
                //addGrades(); not yet declared:3
                break;
            case 4:
                return;
        }
    } while(firstOp != 4);
}

void addSubjects()
{
	cout << "\n\n---------------------------------------------------------\n";
	cout << "Use \'&\' if you are finished inputting your grades.\n";
	char decision = '*';
	int totalSubjects;
	fstream myFile;
	myFile.open("grades.csv", ios::app);
	if (myFile.is_open())
	{
		do
		{
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

void makeFile(string newFileName)
{
	ofstream file;
	file.open(newFileName.c_str());
	if (file.is_open())
	{
		cout << "\nFile has been made succesfully!\n\n";
		file.close();
		return;
	}
}

void addYear()
{
	cout << "Input year: ";
	int year;
	cin >> year;
	cout << "Added " << year;
	string name = "Year\\" + to_string(year);
	if (year % 10 == 1)
	{
		cout << "st ";
		name += "st ";
	}
	else if (year % 10 == 2)
	{
		cout << "nd ";
		name += "nd ";
	}
	else if (year % 10 == 3)
	{
		cout << "rd ";
		name += "rd ";
	}
	else
	{
		cout << "th ";
		name += "th ";
	}

	cout << "year folder.\n\n";
	if(directoryExists(name)) {
		cout << "This year has already been made.\n\n"; 
	} else {
		CreateDirectoryA(name.c_str(), NULL);
	}
	return;
}

void addSemester() {
	cout << "For what year? "; 
	int year; 
	cin >> year; 

	string name = "Year\\" + to_string(year);
	if (year % 10 == 1)
	{
		cout << "st ";
		name += "st ";
	}
	else if (year % 10 == 2)
	{
		cout << "nd ";
		name += "nd ";
	}
	else if (year % 10 == 3)
	{
		cout << "rd ";
		name += "rd ";
	}
	else
	{
		cout << "th ";
		name += "th ";
	}

	if(directoryExists(name)) {
		cout << "Semester folder has been made.\n\n"; 
	} else {
		cout << "This year folder has not been made."; 
	}
}

boolean directoryExists(string& name) { // Simply checks if the file already exists or not, and if it is a directory.
	DWORD attribs = GetFileAttributesA(name.c_str());
    return (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY));
}
