#pragma once

#include "helperMain.hpp"
namespace fs = std::filesystem;

struct subjectGrade{
	string subjectCode;
	string grade;
	string units;
};

// FUNCTION DECLARATIONS
void caseThreeMain();
void displayYear();
void displaySemester();
void displayCGPA();
void loadData(std::vector<subjectGrade> &subjectData, std::vector<string> &header, vector<int> &widths, string fileName);
void displayGrades(std::vector<subjectGrade> &subjectData, std::vector<string> &header, std::vector<int> &widths); // This function: asks for the Year and Semester, after which the grades will be displayed. Only the latter has been implemented so far;
string makeBorder(vector<int> &widths);
void printCentered(string text, int width);
void printLeft(string text, int width);
double calcGWA(std::vector<subjectGrade> &subjectData);
void getValues(std::vector<subjectGrade> &subjectData, double& runningTotal, double& unitsTotal);


// FUNCTION DEFINITIONS
void caseThreeMain(){
	int thirdOp;
	do
	{
		std::cout << "1. Display Year\n";
		std::cout << "2. Display Semester\n";
		std::cout << "3. Display CGPA\n";
		std::cout << "4. Exit\n";
		std::cout << "Choose an option: ";
		std::cin >> thirdOp;
		switch (thirdOp)
		{
		case 1:
			displayYear();
			break;
		case 2:
			displaySemester();
			break;
		case 3:
			displayCGPA();
			break;
		case 4:
			std::cout << "\033[2J\033[1;1H";
			return;
		}
	} while (thirdOp != 4);
}

void displayYear(){
	double runningTotal = 0, unitsTotal = 0;
	cout << "For what year? ";
	int year;
	cin >> year;


	string suffix;
	if (year % 10 == 1) suffix = "st";
	else if (year % 10 == 2) suffix = "nd";
	else if (year % 10 == 3) suffix = "rd";
	else suffix = "th";

	fs::path folderPath = "Year\\" + to_string(year) + suffix;
	
	if (fs::exists(folderPath) && fs::is_directory(folderPath) && !fs::is_empty(folderPath)) {
		std::cout << "\033[2J\033[1;1H";
        
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if(!(std::filesystem::is_empty(entry.path()))){
				for(const auto& subEntry : fs::directory_iterator(entry.path())){
					string fileName;
					std::vector<subjectGrade> subjectData;
					std::vector<string> header;
					std::vector<int> widths;
					fileName = subEntry.path().string();
					std::cout << year << suffix << " Year " << entry.path().filename().string() << " Semester Grades: " << endl;
					loadData(subjectData, header, widths, fileName);
					displayGrades(subjectData, header, widths);
					getValues(subjectData, runningTotal, unitsTotal);
				}
			} else {
				std::cout << year << suffix << " Year " << entry.path().filename().string() << " Semester is empty.\n";
			}
        }
		if(runningTotal != 0){
			std::cout << "+-------------------------+\n";
			std::cout << "| " << "GWA for " << year << suffix << " Year: " << std::fixed << std::setprecision(3) << runningTotal / unitsTotal << " |" << std::endl;
			std::cout << "+-------------------------+" << std::endl << std::endl;
		}
    } else if(fs::exists(folderPath) && fs::is_directory(folderPath) && fs::is_empty(folderPath)) {
		std::cerr << year << suffix << " is empty." << std::endl;
	} else {
        std::cerr << "Provided path is not a valid directory!" << std::endl;
    }
}

void displaySemester(){
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
	fs::path baseDir(name);
	if (fs::exists(baseDir))
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
		if (fs::exists(baseDir))
		{
			fileName = name + "\\grades.csv";
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

void displayCGPA(){
double runningTotal = 0, unitsTotal = 0;

	fs::path folderPath = "Year";
	
	if (fs::exists(folderPath) && fs::is_directory(folderPath) && !fs::is_empty(folderPath)) {
		std::cout << "\033[2J\033[1;1H";
        
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if(!(std::filesystem::is_empty(entry.path()))){
				for(const auto& subEntry : fs::directory_iterator(entry.path())){
					if(fs::is_empty(subEntry)) continue;
					string fileName;
					std::vector<subjectGrade> subjectData;
					std::vector<string> header;
					std::vector<int> widths;
					fileName = subEntry.path().string() + "\\grades.csv";
					loadData(subjectData, header, widths, fileName);
					getValues(subjectData, runningTotal, unitsTotal);
				}
			}
        }
		if(runningTotal != 0){
			std::cout << "+---------------------+\n";
			std::cout << "| " << "Current CGPA: " << std::fixed << std::setprecision(3) << runningTotal / unitsTotal << " |" << std::endl;
			std::cout << "+---------------------+" << std::endl << std::endl;
		}
    }
}

void loadData(std::vector<subjectGrade> &subjectData, std::vector<string> &header, vector<int> &widths, string fileName){
	std::vector<subjectGrade> subjectDataRet;
	std::vector<string> headerRet;
	vector<int> widthsRet;
	std::ostringstream stream;
	fstream f;
	string l;
	int location = 0;
	f.open(fileName, ios::in);
	getline(f, l);
	location = l.find(',');
	headerRet.push_back(l.substr(0, location));
	l = l.substr(location + 1, l.length());
	location = l.find(',');
	headerRet.push_back(l.substr(0, location));
	headerRet.push_back(l.substr(location + 1, l.length()));

	widthsRet.push_back(headerRet[0].length());
	widthsRet.push_back(headerRet[1].length());
	widthsRet.push_back(headerRet[2].length());
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
		double u = std::stod(l);
		stream << std::fixed << std::setprecision(1) << u;
		string uString = stream.str();
		subjectDataRet.push_back({s,gString,uString});
		widthsRet[0] = (s.length() > widthsRet[0]) ? s.length() : widthsRet[0];
		widthsRet[1] = (gString.length() > widthsRet[1]) ? gString.length() : widthsRet[1];
		widthsRet[2] = (uString.length() > widthsRet[2]) ? uString.length() : widthsRet[2];

		stream.str("");
		stream.clear();
	}
	subjectData = subjectDataRet;
	header = headerRet;
	widths = widthsRet;
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

void getValues(std::vector<subjectGrade> &subjectData, double& runningTotal, double& unitsTotal){
	for(subjectGrade& sub : subjectData){
		double u = std::stod(sub.units);
		runningTotal += std::stod(sub.grade) * u;
		unitsTotal += u;
	}
}