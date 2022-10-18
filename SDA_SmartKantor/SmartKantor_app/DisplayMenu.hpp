#pragma once
#include <iostream>
#include <string>
#include "Converter.h"
#include "User.hpp"

class DisplayMenu
{
private:
    User& _userRef;

    Currency::CurrencyCode changeIntToCurrCode(int intToChange);
    void subMenu(std::string operationType);

public:
    DisplayMenu(User& user);
    void mainMenu();
};

std::ostream& operator<< (std::ostream& os, Currency::CurrencyCode currCode);
