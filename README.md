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
- added addYear() functionality. It now creates a folder inside of default empty folder "Year". For some reason, maybe something deeper in the CreateDirectoryA() function, it does not create a file if the file with the same year already exists. 

AUGUST 29, 2026
- attempt to fix addYear() not creating a Year folder.