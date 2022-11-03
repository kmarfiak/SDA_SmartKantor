#include <iostream>

#include "DisplayMenu.hpp"
#include "TempRatesRetriever.hpp"

int main()
{
	TempRatesRetriever tempObj;
	Converter converterObj(tempObj);
	BalanceManager balanceManagerObj;
	Cashier cashierObj(tempObj, converterObj, balanceManagerObj);
	DisplayMenu display(cashierObj);

	display.mainMenu();
}