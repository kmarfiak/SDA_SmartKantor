#pragma once
#include<map>
#include <iomanip>
#include <cmath>


#include "TempRatesRetriever.hpp"

class Converter
{
	TempRatesRetriever& tempRatesRetriever;
	float margin = 0.02;

public:
	//konstruktor co przyjmie temp rates
	Converter(TempRatesRetriever& temp)
		: tempRatesRetriever(temp){}

	float calculateBuy(float amount, Currency::CurrencyCode currCodeSource);
	float calculateSell(float amount, Currency::CurrencyCode currCodeSource);
};

