#include <iostream>
#include<string>

#include "BalanceManager.hpp"




bool BalanceManager::withdraw(Currency::CurrencyCode code, float value)//value jest z klasy User//mozna zmienic nazwe f. na buy?
{
    balance[code] -= value;
    // kompilacja warunkowa do zmiany
#if 0 
    if (value <= Currency::CurrencyCode) // trzeba porownac value z mapa
    {
        return true;
        std::cout << "Na koncie po transakcji pozostalo: " << Currency::CurrencyCode << "EUR";
    }

    else
    {
        value > Currency::CurrencyCode;

        return false;
        std::cout << "Za duza kwota transakcji - mamy jedynie: " << Currency::CurrencyCode;
    }
#endif
    return true;
}

void BalanceManager::deposit(Currency::CurrencyCode code, float depositAmount)//mozna zmienic nazwe f. na buy?
{
    balance[code] += depositAmount;
    std::cout << "Saldo konta kantoru po transakcji to: " << balance[code] << "EUR";
}

bool BalanceManager::readBalance()
{
    // TODO: wczytywac dane z pliku JSON?
    balance[Currency::CurrencyCode::EUR] = 5000.00;
    balance[Currency::CurrencyCode::USD] = 5000.00;
    balance[Currency::CurrencyCode::GBP] = 5000.00;
    balance[Currency::CurrencyCode::CHF] = 5000.00;
    balance[Currency::CurrencyCode::PLN] = 5000.00;
    
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