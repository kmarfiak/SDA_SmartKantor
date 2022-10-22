#include <iostream>

#include "DisplayMenu.hpp"
#include "TempRatesRetriever.hpp"

int main()
{
	TempRatesRetriever tempObj;
	Cashier cashierObj(tempObj);
	DisplayMenu display(cashierObj);

	display.mainMenu();

}