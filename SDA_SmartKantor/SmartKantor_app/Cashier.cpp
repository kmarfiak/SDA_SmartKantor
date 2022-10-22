#include <iostream>
#include <string>

#include "Cashier.hpp"
#include "BalanceManager.hpp"



float Cashier::buy(Currency::CurrencyCode currCodeSource, float amount)
{
    // kupujemy od uzytkownika np. eur
    // zwieksza nam sie euro w balansie, wyplacamy pln
    float value_pln = converter1.calculateBuy(amount, currCodeSource);
    
    _balance.deposit(currCodeSource, amount);
    _balance.withdraw(Currency::CurrencyCode::PLN, value_pln);

    return value_pln;
}

float Cashier::sell(Currency::CurrencyCode currCodeSource, float amount) 
{
    // sprzedajemy euro
    // przybywa pln, ubywa euro
    float value = converter1.calculateSell(amount, currCodeSource);

    _balance.deposit(Currency::CurrencyCode::PLN, value);
    _balance.withdraw(currCodeSource, amount);

    return value;
    
}

std::map<Currency::CurrencyCode, Currency>& Cashier::getRates()
{
    return _tempRates.getRates();
}


 
