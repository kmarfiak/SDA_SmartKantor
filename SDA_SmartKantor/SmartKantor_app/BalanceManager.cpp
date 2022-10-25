#include <iostream>
#include <string>

#include "BalanceManager.hpp"

BalanceManager::BalanceManager()
{
    readBalance();
}

bool BalanceManager::withdraw(Currency::CurrencyCode code, float value)//value jest z klasy User//mozna zmienic nazwe f. na buy?
{  
    if (value <= 0)
    {
        std::cout << "Proba wyplaty kwoty rownej 0 lub ujemnej " << value << " " << code << "Podana kwota powinna byc liczba dodatnia. " << std::endl;
        return false;
    }
    else if (value > balance[code])
    {
        std::cout << "Za duza kwota transakcji " << value << " " << code << " mam jedynie: " << balance[code] << std::endl;
        return false;
    }
    else
    {
        balance[code] -= value;
        std::cout << "Wyplacam " << value << " " << code << ". Zostaje " << balance[code] << " " << code << std::endl;
        return true;
    }
}

void BalanceManager::deposit(Currency::CurrencyCode code, float depositAmount)//mozna zmienic nazwe f. na buy?
{
    balance[code] += depositAmount;
    std::cout << "Po wplacie mam: " << balance[code] << " " << code << std::endl;
}

bool BalanceManager::readBalance()
{
    // TODO: wczytywac dane z pliku JSON?
    balance[Currency::CurrencyCode::EUR] = 5000.00;
    balance[Currency::CurrencyCode::USD] = 5000.00;
    balance[Currency::CurrencyCode::GBP] = 5000.00;
    balance[Currency::CurrencyCode::CHF] = 5000.00;
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