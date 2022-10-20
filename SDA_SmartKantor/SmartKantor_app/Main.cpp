#include <iostream>
#include "DisplayMenu.hpp"
#include "TempRatesRetriever.h"

int main()
{
	TempRatesRetriever tempObj;
	User userObj(tempObj);
	DisplayMenu display(userObj);

	display.mainMenu();

}