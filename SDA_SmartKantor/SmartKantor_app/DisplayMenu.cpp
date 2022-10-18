#include "DisplayMenu.hpp"



Currency::CurrencyCode DisplayMenu::changeIntToCurrCode(int intToChange)
{
    switch (intToChange)
    {
    case 1:
        return Currency::CurrencyCode::EUR;
        break;
    case 2:
        return Currency::CurrencyCode::USD;
        break;
    case 3:
        return Currency::CurrencyCode::GBP;
        break;
    case 4:
        return Currency::CurrencyCode::CHF;
        break;
    }
}

void DisplayMenu::subMenu(std::string operationType)
{
    int currencyTarget = 0;
    std::string lastDisplayMessage = "";

    std::map<Currency::CurrencyCode, Currency>& ratesMap = _userRef.getRates();
    do
    {
        system("cls");
        std::cout << "Jaka walute chcesz " << operationType << "?" << std::endl;
        std::cout << std::endl;
        
        int counter = 1;
        for (auto element : ratesMap)
        {
            std::cout << counter << " - " << element.first << std::endl;
            ++counter;
        }

        std::cout << "0 - Wyjdz" << std::endl << std::endl;

        std::cout << lastDisplayMessage << std::endl << std::endl;

        std::cout << "Co chcesz zrobic?: ";
        std::cin >> currencyTarget;

        if (currencyTarget < 0 || currencyTarget > (counter -1))
        {
            lastDisplayMessage = "Wprowadzono nieprawidlowe polecenie. Prosze wybrac liczbe z podanej listy.";
            continue;
        }

        if (currencyTarget == 0)
        {
            break;
        }

        Currency::CurrencyCode codeTarget = changeIntToCurrCode(currencyTarget);

        system("cls");

        float amount = 0.0f;

        std::cout << "Podaj ilosc: " << std::endl;
        std::cin >> amount;

        if (amount < 0)
        {
            lastDisplayMessage = "Wprowadzono nieprawidlowa kwote. Prosze wybrac walute z listy i podac kwote wieksza od zera. ";
            continue;
        }

        if (operationType == "kupic")
        {
            float bleble = _userRef.buy(codeTarget, amount);
            lastDisplayMessage = "Kupiono " + std::to_string(amount) + " " + codeTarget + " za " + std::to_string(bleble) + " PLN. ";

        }
        else if (operationType == "sprzedac")
        {
            float blabla = _userRef.sell(codeTarget, amount);
            lastDisplayMessage = "Sprzedano " + std::to_string(amount) + " " + codeTarget + " za " + std::to_string(blabla) + " PLN. ";
        }

    } while (currencyTarget != 0);
}

DisplayMenu::DisplayMenu(User& user)
    : _userRef(user)
{
}

void DisplayMenu::mainMenu()
{
    int choice = 0;
    std::string lastDisplayedMessage = "";

    do
    {
        system("cls");

        std::cout << "**** Witamy w SmartKantor ****" << std::endl << std::endl;
        std::cout << "1 - Kupno" << std::endl;
        std::cout << "2 - Sprzedaz" << std::endl;
        std::cout << "3 - Stan kasy (jeszcze nie wspierany)" << std::endl;
        std::cout << "4 - Aktualizuj kursy (jeszcze nie wspierany)" << std::endl;
        std::cout << "5 - Wyswietl aktualne kursy (jeszcze nie wspierany)" << std::endl;
        std::cout << "0 - Wyjdz" << std::endl << std::endl;

        std::cout << lastDisplayedMessage << std::endl << std::endl;
        
        std::cout << "Co chcesz zrobic?: ";
        std::cin >> choice;

        if (choice < 0 || choice > 5)
        {
            lastDisplayedMessage = "Wprowadzono nieprawidlowe polecenie. Prosze wybrac liczbe z podanej listy.";
            continue;
        }

        switch (choice)
        {
        case 1:
            subMenu("kupic"); //dodawanie koncowki do menu zeby byla tylko jedna funkcja bo dziala tak samo dla kupna/sprzedazy
            break;
        case 2:
            subMenu("sprzedac");
            break;
        case 0:
            system("cls");
            std::cout << std::endl << std::endl << "*** Dziekujemy za skorzystanie ze SmartKantor ***" << std::endl << std::endl;
            break;
        }
    } while (choice != 0);
}

std::ostream& operator<<(std::ostream& os, Currency::CurrencyCode currCode)
{
    switch (currCode)
    {
    case Currency::CurrencyCode::CHF:
        return os << "CHF";
        break;
    case Currency::CurrencyCode::EUR:
        return os << "EUR";
        break;
    case Currency::CurrencyCode::GBP:
        return os << "GBP";
        break;
    case Currency::CurrencyCode::PLN:
        return os << "PLN";
        break;
    case Currency::CurrencyCode::USD:
        return os << "USD";
        break;
    }  
}

std::string operator+(std::string str, Currency::CurrencyCode currCode)
{
    switch (currCode)
    {
    case Currency::CurrencyCode::CHF:
        return str + "CHF";
        break;
    case Currency::CurrencyCode::EUR:
        return str + "EUR";
        break;
    case Currency::CurrencyCode::GBP:
        return str + "GBP";
        break;
    case Currency::CurrencyCode::PLN:
        return str + "PLN";
        break;
    case Currency::CurrencyCode::USD:
        return str + "USD";
        break;
    }
  
}
