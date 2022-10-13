#pragma once
#include <iostream>
#include <string>

enum class  CurrencyCode // do usuniecia jak zrobimy enum class gdzies nad Currency
{
    EUR, USD, GBP, CHF, PLN
};

class User  // ta klasy sa tylko na potrzeby dzialania menu,  do usuniecia jak powstanie wlasciwa klasa User
{
public:
    float buy(CurrencyCode currCodeSource, float amount);
};

class DisplayMenu
{
private:
    User& _userRef; 

    CurrencyCode changeIntToCurrCode(int intToChange);
    void subMenu(std::string operationType);

public:
    DisplayMenu(User& user);
    void mainMenu();
};
