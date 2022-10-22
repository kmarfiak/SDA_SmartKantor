#pragma once
#include <iostream>
#include <string>

#include "Converter.hpp"
#include "Cashier.hpp"

enum class Menu
{
    MainMenu, MenuBuy, MenuSell, MenuAmount, ExitOption
};

class DisplayMenu
{
private:
    Cashier& _cashierRef;

    void subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef);
    void subMenuAmount(std::string& amount, Currency::CurrencyCode& currCode, std::string& operationType, std::string& lastDisplayedMessage, Menu& menuRef);
    void initialMenu(std::string& lastDisplayedMessage, Menu& menu);
public:
    DisplayMenu(Cashier& cashier);
    void mainMenu();
};

std::ostream& operator<< (std::ostream& os, Currency::CurrencyCode currCode);

std::string operator+ (std::string str, Currency::CurrencyCode currCode);
