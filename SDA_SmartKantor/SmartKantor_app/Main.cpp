#include <iostream>

#include "DisplayMenu.hpp"
#include "TempRatesRetriever.hpp"

int main()
{
	TempRatesRetriever tempObj;
	Converter converterObj(tempObj);
	Cashier cashierObj(tempObj, converterObj);
	DisplayMenu display(cashierObj);

	display.mainMenu();
}