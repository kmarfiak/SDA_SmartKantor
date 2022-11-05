#pragma once
#include <iostream>
#include <string>

#include "Converter.hpp"
#include "Cashier.hpp"

//enum class trzymaj¹ca wszystkie rodzaje submenu dostepne w DisplayMenu, jest uzywane w g³ównej pêtli MainMenu
//do wyboru odpowiedniego submenu
enum class Menu
{
    MainMenu, MenuBuy, MenuSell, MenuAmount, MenuBalance, MenuReport, MenuRates, ExitOption
};

class DisplayMenu
{
private:
    // referencja do obiektu Cashier, który oddziela warstwe interfejsu od funkcjonalnoœci kantora (dzieki temu moga sie komunikowac)
    // & bo nie chcemy mieæ kolejnych kopii Cashiera
    Cashier& _cashierRef;

    // kupno/sprzeda¿ (operationType), po wyborze waluty (CurrencyCode) przechodzi do MenuAmount
    void subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef);
    // s³u¿y do pobrania iloœci waluty do wymiany (amount) i w zaleznosci od rodzaju operacji wywo³a metode buy albo sell z Cashiera
    void subMenuAmount(std::string& amount, Currency::CurrencyCode& currCode, std::string& operationType, 
                       std::string& lastDisplayedMessage, Menu& menuRef);
    // initialMenu wyswietla funkcjonalnosci kantoru dostepne po wlaczeniu programu
    void initialMenu(std::string& lastDisplayedMessage, Menu& menuRef);
    // subMenuBalance s³u¿y tylko do wyœwietlania stanu kasy
    void subMenuBalance(std::string& lastDisplayedMessage, Menu& menuRef);
    // reportsMenu wyswietla raporty kupna/sprzeda¿y
    void reportsMenu(std::string& lastDisplayedMessage, Menu& menuRef);
    // ratesMenu wyœwietla aktualne kursy
    void ratesMenu(std::string& lastDisplayedMessage, Menu& menuRef);
public:
    // konstruktor parametrowy który tworzy referencje do obiektu Cashier
    DisplayMenu(Cashier& cashier);
    // metoda startuj¹ca g³ówne menu
    void mainMenu();
};


