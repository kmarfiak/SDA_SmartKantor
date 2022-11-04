#pragma once
#include<string>

class Currency
{
	std::string currencyTarget;
	std::string codeName;
	float buyPrice;
	float sellPrice;
	std::string currencySource = "PLN";

public:
	Currency(std::string currencyTarget, std::string codeName, float buyPrice, float sellPrice);
	Currency();
	void setBuyPrice(float newBuyPrice);
	void setSellPrice(float newSellPrice);
	void setCurrencySource(std::string currencySource);
	float getBuyPrice();
	float getSellPrice();
	std::string getCurrencySource();
	std::string getCurrencyTarget();
	std::string getCurrencyCode();

	enum class CurrencyCode
	{
		USD, AUD, CAD, EUR, HUF, CHF, GBP, JPY, CZK,
		DKK, NOK, SEK, XDR, PLN
	};
};

std::ostream& operator<< (std::ostream& os, Currency::CurrencyCode currCode);

std::string operator+ (std::string str, Currency::CurrencyCode currCode);

std::string changeEnumToString(Currency::CurrencyCode currCode);

Currency::CurrencyCode changeStringToEnum(std::string currCode);