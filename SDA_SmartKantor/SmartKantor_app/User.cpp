#include <string>
#include <iostream>

#include "User.hpp"



float User::buy(Currency::CurrencyCode currCodeSource, float amount)

{
    float value = converter1.calculateBuy(amount, currCodeSource);
    return value;
}

float User::sell(Currency::CurrencyCode currCodeSource, float amount) {
    float value = converter1.calculateSell(amount, currCodeSource);
    return value;
}

std::map<Currency::CurrencyCode, Currency>& User::getRates()
{
    return _tempRates.getRates();
}


 
