#pragma once

#include "helperMain.hpp"

// FUNCTION DECLARATIONS
void caseFourMain();
void removeYear();                 // removes specified year.
void removeSemester();             // removes specified semester.
void removeGrades();               // removes grades.csv files.
void removeSubject();               // removes a subject from a grades.csv file.

// FUNCTION DEFINITIONS
void caseFourMain()
{
    int firstOp;
    do
    {
        cout << "1. Remove Year\n";
        cout << "2. Remove Semester\n";
        cout << "3. Remove Grades\n";
        cout << "4. Remove Subject\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> firstOp;
        switch (firstOp)
        {
        case 1:
            removeYear();
            break;
        case 2:
            removeSemester();
            break;
        case 3:
            removeGrades();
            break;
        case 4:
            removeSubject();
            break;
        case 5:
            std::cout << "\033[2J\033[1;1H";
            return;
        }
    } while (firstOp != 5);
}

void removeYear() {
    cout << "Input year: ";
    int year;
    cin >> year;

    string suffix;
    string name = "Year/" + to_string(year);

    if (year % 10 == 1) {
        suffix = "st ";
        name += "st";
    } else if (year % 10 == 2) {
        suffix = "nd ";
        name += "nd";
    } else if (year % 10 == 3) {
        suffix = "rd ";
        name += "rd";
    } else {
        suffix = "th ";
        name += "th";
    }

    fs::path yearDir(name);

    if (fs::exists(yearDir)) {
        fs::remove_all(yearDir); 
        cout << "\nThe " << year << suffix << "year folder and all contents have been deleted.\n\n";
    } else {
        cout << "\nThis year has never been made.\n";
    }
}

void removeSemester() {
    cout << "Input year: ";
    int year;
    cin >> year;

    string name = "Year/" + to_string(year);

    if (year % 10 == 1)
        name += "st";
    else if (year % 10 == 2)
        name += "nd";
    else if (year % 10 == 3)
        name += "rd";
    else
        name += "th";

    fs::path yearDir(name);

    if (fs::exists(yearDir)) {
        cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
        string semNumber;
        cin >> semNumber;

        if (semNumber != "First" && semNumber != "Second" && semNumber != "Third") {
            cout << "This semester is invalid.\n";
            return;
        }

        fs::path semDir = yearDir / semNumber;

        if (fs::exists(semDir)) {
            fs::path gradesFile = semDir / "grades.csv";

            if (fs::exists(gradesFile)) {
                fs::remove(gradesFile); 
            }

            fs::remove_all(semDir); 
            cout << "Removed semester folder.\n\n";
        } else {
            cout << "Semester folder has not yet been made.\n\n";
        }
    } else {
        cout << "\nThis year has never been made.\n";
    }
}

void removeGrades() {
    cout << "Input year: ";
    int year;
    cin >> year;

    string suffix;
    string name = "Year/" + to_string(year);

    if (year % 10 == 1) {
        suffix = "st ";
        name += "st";
    } else if (year % 10 == 2) {
        suffix = "nd ";
        name += "nd";
    } else if (year % 10 == 3) {
        suffix = "rd ";
        name += "rd";
    } else {
        suffix = "th ";
        name += "th";
    }

    fs::path yearDir(name);

    if (fs::exists(yearDir)) {
        cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
        string semNumber;
        cin >> semNumber;

        if (semNumber != "First" && semNumber != "Second" && semNumber != "Third") {
            cout << "This semester is invalid.\n";
            return;
        }

        fs::path semDir = yearDir / semNumber;
        if (fs::exists(semDir)) {
            fs::path gradesFile = semDir / "grades.csv";

            if (fs::exists(gradesFile)) {
                fs::remove(gradesFile); 
                cout << "Removed grades in this semester.\n\n";
            } else {
                cout << "Grades in this semester were never made.\n\n";
                return;
            }
        } else {
            cout << "Semester folder has not yet been made.\n\n";
            return;
        }
    } else {
        cout << "\nThis year has never been made.\n";
    }
}

void removeSubject(){
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

            int flag = 0;
            string subRem;
            std::cout << "Enter subject code: ";
            std::cin >> subRem;
			std::ifstream fileIn(filePath);
            vector<string> loadedLines;
            string tmp;
            while(getline(fileIn, tmp)){
                if(!(tmp.find(subRem) != std::string::npos)) loadedLines.push_back(tmp);
                else flag = 1;
            }
            fileIn.close();
            std::ofstream fileOut(filePath, std::ios::out | std::ios::trunc);
            for(string s : loadedLines) fileOut << s << "\n";
            fileOut.close();
			if(flag) std::cout << "Subject removed successfully.\n\n";
            else std::cout << "Subject not found.\n\n";
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