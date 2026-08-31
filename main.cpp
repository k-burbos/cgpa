#include "helper/helperMain.hpp"

int main(int argc, char **argv)
{
	std::cout << "\033[2J\033[1;1H";
	int mainOp;
	do
	{
		mainOp = opFunc();
		switch (mainOp)
		{
			case 1:
				caseOneMain();
				break;
			case 2:
				caseTwoMain(); // I transferred your 6 glorious lines of code sa 2Edit.hpp inside this function. 
				break;
			case 3:
				caseThreeMain();
				break;
			case 4:
				caseFourMain();
				break;
			case 5:
				std::cout << "\033[2J\033[1;1H";
				return 0;
		}
	} while (mainOp != 5);
	return 0;
}