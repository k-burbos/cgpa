#pragma once

#include "helperMain.hpp"

// FUNCTION DECLARATIONS
void caseTwoMain();


// FUNCTION DEFINITIONS
void caseTwoMain(){
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
            string subCode, editedString = "";
            std::ostringstream stream;
            double subGrade, subUnits;
            std::cout << "Enter subject code: ";
            std::cin >> subCode;
            std::cout << "Enter subject new grade: ";
            std::cin >> subGrade;
            std::cout << "Enter subject new units: ";
            std::cin >> subUnits;
            stream << std::fixed << std::setprecision(1) << subGrade;
            editedString += subCode + "," + stream.str();
            stream.str("");
            stream.clear();
            stream << std::fixed << std::setprecision(1) << subUnits;
            editedString += "," + stream.str();
            
			std::ifstream fileIn(filePath);
            vector<string> loadedLines;
            string tmp;
            while(getline(fileIn, tmp)){
                if(!(tmp.find(subCode) != std::string::npos)) loadedLines.push_back(tmp);
                else{
                    loadedLines.push_back(editedString);
                    flag = 1;
                }
            }
            fileIn.close();
            std::ofstream fileOut(filePath, std::ios::out | std::ios::trunc);
            for(string s : loadedLines) fileOut << s << "\n";
            fileOut.close();
			if(flag) std::cout << "Subject edited successfully.\n\n";
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