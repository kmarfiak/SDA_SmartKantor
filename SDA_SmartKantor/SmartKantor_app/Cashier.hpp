#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "TempRatesRetriever.hpp"
#include "Converter.hpp"
#include "BalanceManager.hpp"

class Cashier
{ 
	Converter& converter1;
	BalanceManager _balance;
	TempRatesRetriever& _tempRates;

public:
	Cashier(TempRatesRetriever& temp, Converter& converterRef)
		: _tempRates(temp), converter1(converterRef) {};

	//kantor kupuje walute
	float buy(Currency::CurrencyCode currCodeSource, float amount);

	//kantor sprzedaje walute
	float sell(Currency::CurrencyCode currCodeSource, float amount);

	std::vector<std::string> getReport();

	std::map<Currency::CurrencyCode, Currency>& getRates();

	std::map<Currency::CurrencyCode, float>& getBalance();

	void updateRates();
};