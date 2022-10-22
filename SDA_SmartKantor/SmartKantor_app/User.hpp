#pragma once
#include <iostream>
#include <string>

#include "TempRatesRetriever.h"
#include "Converter.h"
#include "BalanceManager.hpp"

class User
{ 
private:
	Converter converter1;
	BalanceManager _balance;
	TempRatesRetriever& _tempRates;

public:
	User(TempRatesRetriever& temp)
		: _tempRates(temp) {}

	//kantor kupuje walute
	float buy(Currency::CurrencyCode currCodeSource, float amount);

	//kantor sprzedaje walute
	float sell(Currency::CurrencyCode currCodeSource, float amount);

	std::map<Currency::CurrencyCode, Currency>& getRates();
};