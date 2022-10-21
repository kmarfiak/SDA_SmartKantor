#pragma once
#include <iostream>
#include <string>

#include "TempRatesRetriever.h"
#include "Converter.h"

class User
{ 
	Converter converter1;
	TempRatesRetriever& _tempRates;

public:
	User(TempRatesRetriever& temp)
		: _tempRates(temp) {}

	float buy(Currency::CurrencyCode currCodeSource, float amount);

	float sell(Currency::CurrencyCode currCodeSource, float amount);

	std::map<Currency::CurrencyCode, Currency>& getRates();
};