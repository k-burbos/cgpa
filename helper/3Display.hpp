#pragma once

#include "helperMain.hpp"

// FUNCTION DECLARATIONS
void caseThreeMain();
double calcGWA(); // This function just calculates the GWA.
void displayGrades(); // This function: asks for the Year and Semester, after which the grades will be displayed. Only the latter has been implemented so far;


// FUNCTION DEFINITIONS
void caseThreeMain(){
    displayGrades();
}

double calcGWA()
{
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

void displayGrades()
{
	fstream f;
	string l;
	int location = 0;
	f.open("grades.csv", ios::in);
	std::cout << std::endl;
	while (getline(f, l))
	{
		std::cout << "|\t";
		location = l.find(',');
		string tmp = l.substr(0, location);
		std::cout << tmp;
		if (tmp.length() >= 9)
			std::cout << "\t|\t";
		else
			std::cout << "\t\t|\t";
		l = l.substr(location + 1, l.length());
		location = l.find(',');
		tmp = l.substr(0, location);
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