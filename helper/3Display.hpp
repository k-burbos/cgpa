#pragma once

#include "helperMain.hpp"

struct subjectGrade{
	string subjectCode;
	string grade;
	string units;
};

// FUNCTION DECLARATIONS
void caseThreeMain();
std::vector<subjectGrade> loadData();
double calcGWA(); // This function just calculates the GWA.
void displayGrades(std::vector<subjectGrade> subjectData); // This function: asks for the Year and Semester, after which the grades will be displayed. Only the latter has been implemented so far;


// FUNCTION DEFINITIONS
void caseThreeMain(){
	std::vector<subjectGrade> subjectData = loadData();
    displayGrades(subjectData);
}

double calcGWA()
{
	fstream f;
	string l = "";
	int location = 0;
	double ret = 0, unitTotal = 0;
	f.open("grades.csv", ios::in);
	getline(f,l);
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
//		std::cout << tmp << ": " << grade << ", " << unit << endl;
	}
	return ret / unitTotal;
}

void displayGrades(std::vector<subjectGrade> subjectData)
{
	std::vector<string> header(3);
	fstream f;
	string l;
	int location = 0;
	f.open("grades.csv", ios::in);
	getline(f, l);
	location = l.find(',');
	header[0] = l.substr(0, location);
	l = l.substr(location + 1, l.length());
	location = l.find(',');
	header[1] = l.substr(0, location);
	header[2] = l.substr(location + 1, l.length());
	for(auto& sub : subjectData)
	{
		std::cout << "|\t";
		std::cout << sub.subjectCode;
		if (sub.subjectCode.length() >= 9) std::cout << "\t|\t";
		else std::cout << "\t\t|\t";
		std::cout << sub.grade;
		std::cout << "\t|\t";
		std::cout << sub.units;
		std::cout << "\t|\n";
	}
	std::printf("GWA: %.3f\n", calcGWA());
}

std::vector<subjectGrade> loadData(){
	std::ostringstream stream;
	std::vector<subjectGrade> ret;
	fstream f;
	string l;
	int location = 0;
	f.open("grades.csv", ios::in);
	getline(f, l);
	while (getline(f, l))
	{
		string tmp;
		location = l.find(',');
		string s = l.substr(0, location);
		l = l.substr(location + 1, l.length());

		location = l.find(',');
		tmp = l.substr(0, location);
		double g = std::stod(tmp);
		stream << std::fixed << std::setprecision(1) << g;
		string gString = stream.str();

		stream.str("");
		stream.clear();
		
		l = l.substr(location + 1, l.length());
		double u = std::stod(tmp);
		stream << std::fixed << std::setprecision(1) << u;
		string uString = stream.str();
		ret.push_back({s,gString,uString});

		stream.str("");
		stream.clear();
	}
	return ret;
}