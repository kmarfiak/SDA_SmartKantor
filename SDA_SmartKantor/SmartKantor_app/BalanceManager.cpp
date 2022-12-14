#include <iostream>
#include <string>
#include "BalanceManager.hpp"
#include <sstream>
#include <iomanip>

BalanceManager::BalanceManager()
{
    readBalance();
}

bool BalanceManager::withdraw(Currency::CurrencyCode code, float value)//value jest z klasy User//mozna zmienic nazwe f. na buy?
{
    if (value > balance[code])
    {
        std::stringstream ssValue;
        ssValue << std::fixed << std::setprecision(2) << balance[code];
        throw std::out_of_range("Zbyt duza kwota do wyplaty. W kasie jest tylko " + ssValue.str() + " " + changeEnumToString(code));
        return false;
    }
    else
    {
        balance[code] -= value;
        return true;
    }
}

void BalanceManager::deposit(Currency::CurrencyCode code, float depositAmount)//mozna zmienic nazwe f. na buy?
{
    balance[code] += depositAmount;
}

bool BalanceManager::readBalance()
{
    // TODO: wczytywac dane z pliku JSON?
    balance[Currency::CurrencyCode::USD] = 5000.00;
    balance[Currency::CurrencyCode::AUD] = 5000.00;
    balance[Currency::CurrencyCode::CAD] = 5000.00;
    balance[Currency::CurrencyCode::EUR] = 5000.00;
    balance[Currency::CurrencyCode::HUF] = 5000.00;
    balance[Currency::CurrencyCode::CHF] = 5000.00;
    balance[Currency::CurrencyCode::GBP] = 5000.00;
    balance[Currency::CurrencyCode::JPY] = 5000.00;
    balance[Currency::CurrencyCode::CZK] = 5000.00;
    balance[Currency::CurrencyCode::DKK] = 5000.00;
    balance[Currency::CurrencyCode::NOK] = 5000.00;
    balance[Currency::CurrencyCode::SEK] = 5000.00;
    balance[Currency::CurrencyCode::PLN] = 20000.00;
    return true;
}

bool BalanceManager::storeBalance()
{
    // TODO: zapisz do pliku na koniec dnia, tak aby moc kolejnego dnia odczytac realny stan posiadania
    return true;
}

std::map<Currency::CurrencyCode, float>& BalanceManager::getBalance()
{
    return balance;
}