#pragma once

#include "helperMain.hpp"

// FUNCTION DECLARATIONS
void caseFourMain();
void removeYear();                 // removes specified year.
void removeSemester();             // removes specified semester.
void removeGrades();               // removes grades.csv files.
bool deleteDirectory(string path); // removes everything inside of the year file to delete.

// FUNCTION DEFINITIONS
void caseFourMain()
{
    int firstOp;
    do
    {
        cout << "1. Remove Year\n";
        cout << "2. Remove Semester\n";
        cout << "3. Remove Grades\n";
        cout << "4. Exit\n";
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
            std::cout << "\033[2J\033[1;1H";
            return;
        }
    } while (firstOp != 4);
}

void removeYear()
{
    cout << "Input year: ";
    int year;
    cin >> year;
    string suffix;
    string name = "Year\\" + to_string(year);

    if (year % 10 == 1)
    {
        suffix = "st ";
        name += "st";
    }
    else if (year % 10 == 2)
    {
        suffix = "nd ";
        name += "nd";
    }
    else if (year % 10 == 3)
    {
        suffix = "rd ";
        name += "rd";
    }
    else
    {
        suffix = "th ";
        name += "th";
    }
    if (directoryExists(name))
    {
        deleteDirectory(name);
        cout << "\nThe " << year << suffix << "year folder and all contents have been deleted.\n\n";
    }
    else
    {
        cout << "\nThis year has never been made.\n";
    }
}

void removeSemester()
{
    cout << "Input year: ";
    int year;
    cin >> year;

    string name = "Year\\" + to_string(year);

    if (year % 10 == 1)
        name += "st";
    else if (year % 10 == 2)
        name += "nd";
    else if (year % 10 == 3)
        name += "rd";
    else
        name += "th";

    if (directoryExists(name))
    {
        cout << "First, second, or third? (Answer \"First\", \"Second\", or \"Third\".): ";
        string semNumber;
        cin >> semNumber;

        if (semNumber != "First" && semNumber != "Second" && semNumber != "Third")
        {
            cout << "This semester is invalid.\n";
            return;
        }

        string semPath = name + "\\" + semNumber;

        if (directoryExists(semPath))
        {
            string gradesFile = semPath + "\\grades.csv";

            if (filePathExists(gradesFile))
            { // this function just deletes grades.csv file
                DeleteFileA(gradesFile.c_str());
            }

            RemoveDirectoryA(semPath.c_str()); // this is the actual delete semester folder function
            cout << "Removed semester folder.\n\n";
        }
        else
        {
            cout << "Semester folder has not yet been made.\n\n";
        }
    }
    else
    {
        cout << "\nThis year has never been made.\n";
    }
}

void removeGrades()
{
    cout << "Input year: ";
    int year;
    cin >> year;
    string name = "Year\\" + to_string(year);
    string suffix;
    if (year % 10 == 1)
    {
        suffix = "st ";
        name += "st";
    }
    else if (year % 10 == 2)
    {
        suffix = "nd ";
        name += "nd";
    }
    else if (year % 10 == 3)
    {
        suffix = "rd ";
        name += "rd";
    }
    else
    {
        suffix = "th ";
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
            name += "\\grades.csv";
            if (filePathExists(name))
            {
                remove(name.c_str());
                cout << "Removed grades in this semester.\n\n";
            }
            else
            {
                cout << "Grades in this semester were never made.\n\n";
                return;
            }
        }
        else
        {
            cout << "Semester folder has not yet been made.\n\n";
            return;
        }
    }
    else
    {
        cout << "\nThis year has never been made.\n";
    }
    return;
}

bool deleteDirectory(string path)
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA((path + "\\*").c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    do
    {
        string fileName = findData.cFileName;

        if (fileName == "." || fileName == "..")
            continue;

        string fullPath = path + "\\" + fileName;

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            deleteDirectory(fullPath);
            RemoveDirectoryA(fullPath.c_str());
        }
        else
        {
            DeleteFileA(fullPath.c_str());
        }
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);

    return RemoveDirectoryA(path.c_str());
}