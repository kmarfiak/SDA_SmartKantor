#pragma once
#include <iostream>
#include <string>

#include "Converter.hpp"
#include "Cashier.hpp"

//enum class trzymaj�ca wszystkie rodzaje submenu dostepne w DisplayMenu, jest uzywane w g��wnej p�tli MainMenu
//do wyboru odpowiedniego submenu
enum class Menu
{
    MainMenu, MenuBuy, MenuSell, MenuAmount, MenuBalance, MenuReport, MenuRates, ExitOption
};

class DisplayMenu
{
private:
    // referencja do obiektu Cashier, kt�ry oddziela warstwe interfejsu od funkcjonalno�ci kantora (dzieki temu moga sie komunikowac)
    // & bo nie chcemy mie� kolejnych kopii Cashiera
    Cashier& _cashierRef;

    // kupno/sprzeda� (operationType), po wyborze waluty (CurrencyCode) przechodzi do MenuAmount
    void subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef);
    // s�u�y do pobrania ilo�ci waluty do wymiany (amount) i w zaleznosci od rodzaju operacji wywo�a metode buy albo sell z Cashiera
    void subMenuAmount(std::string& amount, Currency::CurrencyCode& currCode, std::string& operationType, 
                       std::string& lastDisplayedMessage, Menu& menuRef);
    // initialMenu wyswietla funkcjonalnosci kantoru dostepne po wlaczeniu programu
    void initialMenu(std::string& lastDisplayedMessage, Menu& menuRef);
    // subMenuBalance s�u�y tylko do wy�wietlania stanu kasy
    void subMenuBalance(std::string& lastDisplayedMessage, Menu& menuRef);
    // reportsMenu wyswietla raporty kupna/sprzeda�y
    void reportsMenu(std::string& lastDisplayedMessage, Menu& menuRef);
    // ratesMenu wy�wietla aktualne kursy
    void ratesMenu(std::string& lastDisplayedMessage, Menu& menuRef);
public:
    // konstruktor parametrowy kt�ry tworzy referencje do obiektu Cashier
    DisplayMenu(Cashier& cashier);
    // metoda startuj�ca g��wne menu
    void mainMenu();
};


