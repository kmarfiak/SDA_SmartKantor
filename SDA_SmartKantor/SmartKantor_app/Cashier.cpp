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
    tlogger.log(currCode, amount, value_pln, "kupno");
    _balance.deposit(currCode, amount);
    _balance.withdraw(Currency::CurrencyCode::PLN, value_pln);

    return value_pln;
}

float Cashier::sell(Currency::CurrencyCode currCode, float amount) 
{
    TransactionLogger tlogger;
    // sprzedajemy euro
    // przybywa pln, ubywa euro
    float value = converter1.calculateSell(amount, currCode);
    tlogger.log(currCode, amount, value, "sprzedaz");

    _balance.deposit(Currency::CurrencyCode::PLN, value);
    _balance.withdraw(currCode, amount);

    return value;
    
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


 
