#pragma once

#include "helperMain.hpp"

struct subjectGrade{
	string subjectCode;
	string grade;
	string units;
};

// FUNCTION DECLARATIONS
void caseThreeMain();
void loadData(std::vector<subjectGrade> &subjectData, std::vector<string> &header, vector<int> &widths, string fileName);
void displayGrades(std::vector<subjectGrade> &subjectData, std::vector<string> &header, std::vector<int> &widths); // This function: asks for the Year and Semester, after which the grades will be displayed. Only the latter has been implemented so far;
string makeBorder(vector<int> &widths);
void printCentered(string text, int width);
void printLeft(string text, int width);
double calcGWA(std::vector<subjectGrade> &subjectData);


// FUNCTION DEFINITIONS
void caseThreeMain(){
	string fileName;
	std::vector<subjectGrade> subjectData;
	std::vector<string> header;
	std::vector<int> widths;

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
			string fileName = name + "\\grades.csv";
			std::cout << endl;
			std::cout << "\033[2J\033[1;1H";
			std::cout << year << suffix << " Year " << semNumber << " Semester Grades: " << endl;
			loadData(subjectData, header, widths, fileName);
			displayGrades(subjectData, header, widths);
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

void loadData(std::vector<subjectGrade> &subjectData, std::vector<string> &header, vector<int> &widths, string fileName){
	std::ostringstream stream;
	fstream f;
	string l;
	int location = 0;
	f.open(fileName, ios::in);
	getline(f, l);
	location = l.find(',');
	header.push_back(l.substr(0, location));
	l = l.substr(location + 1, l.length());
	location = l.find(',');
	header.push_back(l.substr(0, location));
	header.push_back(l.substr(location + 1, l.length()));

	widths.push_back(header[0].length());
	widths.push_back(header[1].length());
	widths.push_back(header[2].length());
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
		subjectData.push_back({s,gString,uString});
		widths[0] = (s.length() > widths[0]) ? s.length() : widths[0];
		widths[1] = (gString.length() > widths[1]) ? gString.length() : widths[1];
		widths[2] = (uString.length() > widths[2]) ? uString.length() : widths[2];

		stream.str("");
		stream.clear();
	}
}

void displayGrades(std::vector<subjectGrade> &subjectData,  std::vector<string> &header, std::vector<int> &widths)
{
	string border = makeBorder(widths);
	std::cout << border << std::endl;
	printCentered(header[0], widths[0]);
	printCentered(header[1], widths[1]);
	printCentered(header[2], widths[2]);
	std::cout << "|\n";
	std::cout << border << std::endl;
	for(auto& sub : subjectData){
		printLeft(sub.subjectCode, widths[0]);
		printCentered(sub.grade, widths[1]);
		printCentered(sub.units, widths[2]);
		std::cout << "|\n";
	}
	std::cout << border << std::endl;
	std::printf("GWA: %.3f\n", calcGWA(subjectData));
	std::cout << std::endl;
}

string makeBorder(vector<int> &widths){
	string ret = "+";
	for(int width : widths) ret += string(width + 2, '-') + '+';
	return ret;
}

double calcGWA(std::vector<subjectGrade> &subjectData)
{
	double ret = 0, unitTotal = 0;
	for(auto& sub : subjectData){
		double grade = std::stod(sub.grade);
		double unit = std::stod(sub.units);
		ret += grade * unit;
		unitTotal += unit;
	}
	return ret / unitTotal;
}

void printCentered(string text, int width){
	int total_padding = width - text.length();
	int left_padding = total_padding / 2;
	
	std::cout << "| " << setw(left_padding + text.length()) << right << text;
	std::cout << setw(width - (left_padding + text.length())) << "";
	std::cout << " ";
}

void printLeft(string text, int width){
	std::cout << "| " << left << setw(width) << text << " ";
}