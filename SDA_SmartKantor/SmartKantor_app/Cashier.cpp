#include <iostream>
#include <string>
#include <vector>

#include "Cashier.hpp"
#include "BalanceManager.hpp"
#include "TransactionLogger.hpp"



float Cashier::buy(Currency::CurrencyCode currCode, float amount)
{
    TransactionLogger tlogger;
    // kupujemy od uzytkownika np. eur
    // zwieksza nam sie euro w balansie, wyplacamy pln
    float value_pln = converter1.calculateBuy(amount, currCode);
   
    if (_balance.withdraw(Currency::CurrencyCode::PLN, value_pln) == true)
    {
        tlogger.log(currCode, amount, value_pln, "kupno"); // przenioslam loggera tutaj zeby logowal transakcje tylko gdy sie udadza 
        _balance.deposit(currCode, amount);
        return value_pln;
    }
    else
    {  // za maly balans wiec zwroc 0, transakcja nie doszla do skutku
        return 0;
    }
}

float Cashier::sell(Currency::CurrencyCode currCode, float amount) 
{
    TransactionLogger tlogger;
    // sprzedajemy euro
    // przybywa pln, ubywa euro
    float value = converter1.calculateSell(amount, currCode);

    if ((_balance.withdraw(currCode, amount) == true))
    {
        tlogger.log(currCode, amount, value, "sprzedaz");
        _balance.deposit(Currency::CurrencyCode::PLN, value);
        return value;
    }
    else
    {
        // za maly balans wiec zwroc 0, transakcja nie doszla do skutku
        return 0;
    }
}

std::vector<std::string> Cashier::getReport()
{
    TransactionLogger tlogger;
    return tlogger.getReport();
}

std::map<Currency::CurrencyCode, Currency>& Cashier::getRates()
{
    return _tempRates.getRates();
}

std::map<Currency::CurrencyCode, float>& Cashier::getBalance()
{
    return _balance.getBalance();
}


 
