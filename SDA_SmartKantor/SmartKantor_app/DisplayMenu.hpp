#pragma once
#include <iostream>
#include <string>

#include "Converter.hpp"
#include "Cashier.hpp"

enum class Menu
{
    MainMenu, MenuBuy, MenuSell, MenuAmount, MenuBalance, ExitOption
};

class DisplayMenu
{
private:
    Cashier& _cashierRef;

    void subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef);
    void subMenuAmount(std::string& amount, Currency::CurrencyCode& currCode, std::string& operationType, std::string& lastDisplayedMessage, Menu& menuRef);
    void initialMenu(std::string& lastDisplayedMessage, Menu& menuRef);
    void subMenuBalance(std::string& lastDisplayedMessage, Menu& menuRef);
public:
    DisplayMenu(Cashier& cashier);
    void mainMenu();
};


