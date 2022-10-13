#include "pch.h"
#include "framework.h"
#include "DisplayMenu.hpp"


float User::buy(CurrencyCode currCodeSource, float amount)
{
	return 0.0f;
}

CurrencyCode DisplayMenu::changeIntToCurrCode(int intToChange)
{
    switch (intToChange)
    {
    case 1:
        return CurrencyCode::EUR;
        break;
    case 2:
        return CurrencyCode::USD;
        break;
    case 3:
        return CurrencyCode::GBP;
        break;
    case 4:
        return CurrencyCode::CHF;
        break;
    }
}

void DisplayMenu::subMenu(std::string operationType)
{
    int currencyTarget = 0;
    do
    {
        system("cls");
        std::cout << "Jaka walute chcesz " << operationType << "?" << std::endl;
        std::cout << std::endl;
        std::cout << "1 - EUR" << std::endl;
        std::cout << "2 - USD" << std::endl;
        std::cout << "3 - GBP" << std::endl;
        std::cout << "4 - CHF" << std::endl;
        std::cout << "0 - Wyjdz" << std::endl;
        std::cout << std::endl;

        std::cout << "Co chcesz zrobic?: ";
        std::cin >> currencyTarget;

        if (currencyTarget == 0)
        {
            break;
        }

        CurrencyCode codeTarget = changeIntToCurrCode(currencyTarget);

        system("cls");

        float amountToBuy = 0.0f;

        std::cout << "Podaj ilosc: " << std::endl;
        std::cin >> amountToBuy;

        _userRef.buy(codeTarget, amountToBuy);
        system("cls");

    } while (currencyTarget != 0);
}

DisplayMenu::DisplayMenu(User& user)
    : _userRef(user)
{
}

void DisplayMenu::mainMenu()
{
    int choice = 0;
    do
    {
        system("cls");

        std::cout << "**** Witamy w SmartKantor ****" << std::endl << std::endl;
        std::cout << "1 - Kupno" << std::endl;
        std::cout << "2 - Sprzedaz" << std::endl;
        std::cout << "3 - Stan kasy (jeszcze nie wspierany)" << std::endl;
        std::cout << "4 - Aktualizuj kursy (jeszcze nie wspierany)" << std::endl;
        std::cout << "5 - Wyswietl aktualne kursy (jeszcze nie wspierany)" << std::endl;
        std::cout << "0 - Wyjdz" << std::endl;
        std::cout << std::endl;

        std::cout << "Co chcesz zrobic?: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            subMenu("kupic"); //dodawanie koncowki do menu zeby byla tylko jedna funkcja bo dziala tak samo dla kupna/sprzedazy
            break;
        case 2:
            subMenu("sprzedac");
            break;
        case 0:
            std::cout << "Dziekujemy za skorzystanie ze SmartKantor" << std::endl;;
            break;
        }
    } while (choice != 0);
}
