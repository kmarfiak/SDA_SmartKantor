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

	float calculateBuy(float amount, Currency::CurrencyCode currCodeSource)
	{
		std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();
		float result = amount * (rates[currCodeSource].getBuyPrice());
		float resultMargin = result + (result * margin);
		float resultMarginF = ceil(resultMargin * 100.0) / 100.0;
		return resultMarginF;
	}
	float calculateSell(float amount, Currency::CurrencyCode currCodeSource)
	{
		std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();

		float result = amount * rates[currCodeSource].getSellPrice();
		float resultMargin = result - (result * margin);
		float resultMarginF = ceil(resultMargin * 100.0) / 100.0;
		return resultMarginF;
	}

};

