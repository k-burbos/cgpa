# cgpa

AUGUST 24, 2026 
- added function makeNewFolder(); makes a new folder using the inputted string. 
- added incomplete checkerHeader() function; currently does nothing. 
- added function calcGWA(); calculates the GWA of the grades.csv file.

AUGUST 26, 2026
- renamed function makeNewFolder() into makeNewFile(); 
- reformatted calcGWA(), displays up to 3 decimal points. 
- added addYear() function; currently only displays text to show the function works. It does not actually make a folder.

AUGUST 27, 2026
- added displayGrades() function
- functionalities include taking the year and semester as input, and displaying the grades as output;
- only the latter functionality has been added so far.
- added addYear() functionality. It now creates a folder inside of default empty folder "Year". 

AUGUST 29, 2026
- added addSemester(). Implemented a print statement to tell you if file already exists. 
- removed addSubjects(), replaced with fillGrades() with improved code. 
- removed checkHeader(); 
- added filePathExists() to check if grades.csv file under that year and semester has already been made. 
- added removeYear() function. 
- added removeSemester() function. 
- added removeGrades() function.
- added deleteDirectory() function; 
- removed makeFile() function; obsolete.
- removed directoryExists() function; replaced by <filesystem> imported function.
- removed filePathExists() function. 
- removed deleteDirectory() function, replaced by remove_all.
        FIX LOG
        - fixed addYear() not creating a folder. Implemented a print statement to tell you if file already exists. 
        - fixed addGrades() function making a folder instead of a .csv file.
        - fixed issue with removeYear() where it fails to delete year folders if they are not empty.
- added loadData() at 3Display.hpp. loads the file data onto subjectData, header data onto header, and the max widths for each column onto widths
- added displayGrades() at 3Display.hpp which displays the grades.
- added makeBorder() at 3Display.hpp which creates the border (the thing with the plus thingy);
- added printCentered() which prints centered text within a given width;
- added printLeft() which prints left-aligned text within a given width. mainly used for the subject code; 