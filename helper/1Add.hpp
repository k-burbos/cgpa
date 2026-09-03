#pragma once

#include "helperMain.hpp"
namespace fs = filesystem;

// FUNCTION DECLARATIONS
void caseOneMain();
void addGWA();
void addYear();					  // Adds years into Year Folder;
void addSemester();				  // Adds semesters into year folders;
void addGrades();				  // Adds grades.csv files per folder;
void appendGrade();				  // Adds a new grade to grades.csv;
void fillGrades(string filePath); // fills grades.csv file;

// FUNCTION DEFINITIONS
void caseOneMain()
{
	int firstOp;
	do
	{
		std::cout << "1. Add Year\n";
		std::cout << "2. Add Semester\n";
		std::cout << "3. Add Grades\n";
		std::cout << "4. Append New Grade\n";
		std::cout << "5. Exit\n";
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
			appendGrade();
			break;
		case 5:
			std::cout << "\033[2J\033[1;1H";
			return;
		}
	} while (firstOp != 5);
}

void addYear()
{
	cout << "Input year: ";
	int year;
	std::cin >> year;

	cout << "Added " << year;

	string suffix;
	switch (year % 10)
	{
	case 1:
		suffix = "st";
		break;
	case 2:
		suffix = "nd";
		break;
	case 3:
		suffix = "rd";
		break;
	default:
		suffix = "th";
		break;
	}

	cout << suffix << " ";
	string name = "Year/" + std::to_string(year) + suffix;

	fs::path baseDir("Year");
	if (!fs::exists(baseDir))
	{
		fs::create_directory(baseDir);
	}

	cout << "year folder.\n\n";

	fs::path yearDir(name);
	if (fs::exists(yearDir))
	{
		cout << "This year has already been made.\n\n";
	}
	else
	{
		fs::create_directory(yearDir);
	}
}

void addSemester()
{
	cout << "For what year? ";
	int year;
	cin >> year;

	string suffix;
	switch (year % 10)
	{
	case 1:
		suffix = "st";
		break;
	case 2:
		suffix = "nd";
		break;
	case 3:
		suffix = "rd";
		break;
	default:
		suffix = "th";
		break;
	}

	string name = "Year/" + std::to_string(year) + suffix;
	fs::path yearDir(name);

	if (fs::exists(yearDir))
	{
		cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
		string semNumber;
		cin >> semNumber;

		if (semNumber != "First" && semNumber != "Second" && semNumber != "Third")
		{
			cout << "This semester is invalid.\n";
			return;
		}

		fs::path semDir = yearDir / semNumber;
		if (fs::exists(semDir))
		{
			cout << semNumber << " semester for " << year << suffix << " year has already been made.\n\n";
		}
		else
		{
			fs::create_directory(semDir);
			cout << "Semester folder has been made.\n\n";
		}
	}
	else
	{
		std::cout << "This year folder has not been made.\n\n";
	}
}

void addGrades()
{
	cout << "For what year? ";
	int year;
	cin >> year;

	string suffix;
	string name = "Year/" + to_string(year);
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

	fs::path yearDir(name);

	if (fs::exists(yearDir))
	{
		cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
		string semNumber;
		cin >> semNumber;

		if (semNumber != "First" && semNumber != "Second" && semNumber != "Third")
		{
			cout << "This semester is invalid.\n\n";
			return;
		}

		fs::path semDir = yearDir / semNumber;
		if (fs::exists(semDir))
		{
			fs::path filePath = semDir / "grades.csv";

			if (fs::exists(filePath))
			{
				char over;
				cout << "You have already inputted grades for this semester. "
					 << "Would you like to override? (y/n): ";
				cin >> over;
				if (over != 'y' && over != 'Y')
					return;
			}

			ofstream file(filePath);
			if (file.is_open())
			{
				file << "Subject Code, Grade, Unit\n";
				file.close();
			}

			fillGrades(filePath.string());
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
	if (file.is_open())
	{
		cout << "\n\nIf you are finished, please input a \'n\': ";
		char answer = 'y';
		do
		{
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

void appendGrade(){
	cout << "For what year? ";
	int year;
	cin >> year;

	string suffix;
	string name = "Year/" + to_string(year);
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

	fs::path yearDir(name);

	if (fs::exists(yearDir))
	{
		cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
		string semNumber;
		cin >> semNumber;

		if (semNumber != "First" && semNumber != "Second" && semNumber != "Third")
		{
			cout << "This semester is invalid.\n\n";
			return;
		}

		fs::path semDir = yearDir / semNumber;
		if (fs::exists(semDir))
		{
			fs::path filePath = semDir / "grades.csv";

			if (!fs::exists(filePath))
			{
				cout << "Grades file has NOT been created yet.\n\n";
				return;
			}

			fillGrades(filePath.string());
			cout << "Grades successfully appended.\n\n";
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