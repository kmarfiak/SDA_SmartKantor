#pragma once
#include <iostream>
#include <string>
#include "Converter.h"
#include "User.hpp"

enum class Menu
{
    MainMenu, MenuBuy, MenuSell, MenuAmount, ExitOption
};

class DisplayMenu
{
private:
    User& _userRef;

    void subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef);
    void subMenuAmount(std::string& amount, Currency::CurrencyCode& currCode, std::string& operationType, std::string& lastDisplayedMessage, Menu& menuRef);
    void initialMenu(std::string& lastDisplayedMessage, Menu& menu);
public:
    DisplayMenu(User& user);
    void mainMenu();
};

std::ostream& operator<< (std::ostream& os, Currency::CurrencyCode currCode);

std::string operator+ (std::string str, Currency::CurrencyCode currCode);
