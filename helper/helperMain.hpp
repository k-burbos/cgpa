/*
This is here so it doesnt loop.
I declared the helpers here but,
I also declared helper.hpp in each
helper files so it kinda goes in a
loop. This only reads each files 
once so is all good!!
*/
#pragma once

// Import Main Libraries Here
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <filesystem>

// Using Namespace (L behavior btw)
using namespace std;

// Import Helpers
#include "1Add.hpp"
#include "2Edit.hpp"
#include "3Display.hpp"
#include "4Remove.hpp"

// Additional Function/s
int opFunc(){
    int n;
    cout << "1. Add (Year/Sem/Grades)\n";
    cout << "2. Edit Grades\n";
    cout << "3. Display Grades\n";
    cout << "4. Remove (Year/Sem/Grades)\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
    cin >> n;
    return n;
}