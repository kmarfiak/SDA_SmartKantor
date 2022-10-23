#pragma once
#include<map>

#include "TempRatesRetriever.hpp"

class Converter
{
	TempRatesRetriever tempRatesRetriever;
	float margin = 0.02;

public:

	float calculateBuy(float amount, Currency::CurrencyCode currCodeSource)
	{
		std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();
		float result = amount * rates[currCodeSource].getBuyPrice();
		float resultMargin = result + (result * margin);
		return resultMargin;
	}
	float calculateSell(float amount, Currency::CurrencyCode currCodeSource)
	{
		std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();

		float result = amount * rates[currCodeSource].getSellPrice();
		float resultMargin = result + (result * margin);
		return resultMargin;
	}

};

