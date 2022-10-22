#pragma once
#include <iostream>
#include <string>

#include "TempRatesRetriever.hpp"
#include "Converter.hpp"
#include "BalanceManager.hpp"

class Cashier
{ 
	Converter converter1;
	BalanceManager _balance;
	TempRatesRetriever& _tempRates;

public:
	Cashier(TempRatesRetriever& temp)
		: _tempRates(temp) {}

	//kantor kupuje walute
	float buy(Currency::CurrencyCode currCodeSource, float amount);

	//kantor sprzedaje walute
	float sell(Currency::CurrencyCode currCodeSource, float amount);

	std::map<Currency::CurrencyCode, Currency>& getRates();
};