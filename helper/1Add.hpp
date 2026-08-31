#pragma once

#include "helperMain.hpp"

// FUNCTION DECLARATIONS
void caseOneMain();
void addGWA();
void makeFile(string newFileName);
void addYear();						   // Adds years into Year Folder;
void addSemester();					   // Adds semesters into year folders;
void addGrades();					   // Adds grades.csv files per folder;
void fillGrades(string filePath);					   // fills grades.csv file;
boolean directoryExists(string &name); // checks if directory exists;
boolean filePathExists(string name); // checks if file exists; 

// FUNCTION DEFINITIONS
void caseOneMain()
{
	int firstOp;
	do
	{
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
			addGrades();
			break;
		case 4:
			std::cout << "\033[2J\033[1;1H";
			return;
		}
	} while (firstOp != 4);
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

	string checkIfYearFolderExists = "Year";

	if (!directoryExists(checkIfYearFolderExists))
	{
		CreateDirectoryA("Year", NULL);
	}

	cout << "year folder.\n\n";
	if(directoryExists(name))
	{
		cout << "This year has already been made.\n\n";
	}
	else
	{
		CreateDirectoryA(name.c_str(), NULL);
	}
	return;
}

void addSemester()
{
	cout << "For what year? ";
	int year;
	cin >> year;

	string name = "Year\\" + to_string(year);
	string suffix;
	if (year % 10 == 1)
	{
		suffix = "st";
		name += "st";
	}
	else if (year % 10 == 2)
	{
		suffix = "nd";
		name += "nd";
	}
	else if (year % 10 == 3)
	{
		suffix = "rd";
		name += "rd";
	}
	else
	{
		suffix = "th";
		name += "th";
	}

	if (directoryExists(name))
	{
		cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
		string semNumber;
		cin >> semNumber;
		if (semNumber != "First" && semNumber != "Second" && semNumber != "Third")
		{
			cout << "This semester is invalid.";
			return;
		}
		name += "\\" + semNumber;
		if (directoryExists(name))
		{
			cout << semNumber << " semester for " << year << suffix << " year has already been made.\n\n";
			return;
		}
		else
		{
			CreateDirectoryA(name.c_str(), NULL);
			cout << "Semester folder has been made.\n\n";
		}
	}
	else
	{
		cout << "This year folder has not been made.\n\n";
	}
}

void addGrades()
{
	cout << "For what year? ";
	int year;
	cin >> year;

	string name = "Year\\" + to_string(year);
	string suffix;
	if (year % 10 == 1)
	{
		suffix = "st";
		name += "st";
	}
	else if (year % 10 == 2)
	{
		suffix = "nd";
		name += "nd";
	}
	else if (year % 10 == 3)
	{
		suffix = "rd";
		name += "rd";
	}
	else
	{
		suffix = "th";
		name += "th";
	}

	if (directoryExists(name))
	{
		cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
		string semNumber;
		cin >> semNumber;
		if (semNumber != "First" && semNumber != "Second" && semNumber != "Third")
		{
			cout << "This semester is invalid.\n\n";
			return;
		}
		name += "\\" + semNumber;
		if (directoryExists(name))
		{
			string filePath = name + "\\grades.csv";

			if(filePathExists(filePath)) {
				char over; 
				cout << "You have already inputted grades for this semester. Would you like to override? (y/n): ";
				cin >> over; 
				if(over != 'y' && over != 'Y') return; 
			}
			fstream file;
			file.open(filePath, ios::out);
			if (file.is_open())
			{
				file << "Subject Code, Grade, Unit\n";
				file.close();
			}
			fillGrades(filePath);

			cout << "Grades file has been created in your chosen semester.\n\n";
		}
		else
		{
			cout << "This semester has not been made yet.\n\n";
			return;
		}
	}
	else
	{
		cout << "This year folder has not been made.\n\n";
	}
}

void fillGrades(string filePath)
{
	fstream file; 
	file.open(filePath, ios::app); 
	if(file.is_open()) {
		cout << "\n\nIf you are finished, please input a \'n\': "; 
		char answer = 'y'; 
		do {
			string subjectCode;
			double grade, unit; 
			cout << "\nSubject Code: "; 
			cin >> subjectCode; 
			cout << "Grade: ";
			cin >> grade; 
			cout << "Unit: "; 
			cin >> unit; 
			file << subjectCode << ", " << grade << ", " << unit << "\n"; 
			cout << "\nContinue? (y/n): "; 
			cin >> answer;
		} while (answer == 'Y' || answer == 'y'); 
		cout << "Grades have been filled.\n";
	}
}

boolean directoryExists(string &name)
{ // Simply checks if the file already exists or not, and if it is a directory.
	DWORD attribs = GetFileAttributesA(name.c_str());
	return (attribs != INVALID_FILE_ATTRIBUTES && (attribs & FILE_ATTRIBUTE_DIRECTORY));
}

boolean filePathExists(string filePath)
{ // Simply checks if the file already exists or not, and if it is a directory.
	DWORD attribs = GetFileAttributesA(filePath.c_str());
	return (attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY));
}

