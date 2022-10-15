#include <iostream>
#include "DisplayMenu.hpp"


int main()
{
	User userObj;
	DisplayMenu display(userObj);

	display.mainMenu();

}