
#include "Converter.hpp"



float Converter::calculateBuy(float amount, Currency::CurrencyCode currCodeSource)
{
	std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();
	float result = amount * rates[currCodeSource].getBuyPrice();
	float resultMargin = result + (result * margin);
	float resultMarginF = ceil(resultMargin * 100.0) / 100.0;
	return resultMarginF;
}
float Converter::calculateSell(float amount, Currency::CurrencyCode currCodeSource)
{
	std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();

	float result = amount * rates[currCodeSource].getSellPrice();
	float resultMargin = result - (result * margin);
	float resultMarginF = ceil(resultMargin * 100.0) / 100.0;
	return resultMarginF;
}