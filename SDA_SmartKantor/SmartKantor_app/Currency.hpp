#pragma once
#include<string>
//#include "json/json.hpp"

class Currency
{
	std::string currencyTarget;
	std::string codeName;
	float buyPrice;
	float sellPrice;
	std::string currencySource = "PLN";//czyli PLN
public:
	Currency(std::string currencyTarget, std::string codeName, float buyPrice, float sellPrice);
	Currency();
	enum class CurrencyCode
	{
		USD, AUD, CAD, EUR, HUF, CHF, GBP, JPY, CZK,
		DKK, NOK, SEK, XDR, PLN
	};
	float getBuyPrice();
	void setBuyPrice(float newBuyPrice);
	float getSellPrice();
	void setSellPrice(float newSellPrice);
	std::string getCurrencySource();
	std::string getCurrencyTarget();
	std::string getCurrencyCode();
	void setCurrencySource(std::string currencySource);
	//void to_json(json& j, const Currency& s);
	//void from_json(const json& j, Currency& s);
};

std::ostream& operator<< (std::ostream& os, Currency::CurrencyCode currCode);

std::string operator+ (std::string str, Currency::CurrencyCode currCode);

std::string changeEnumToString(Currency::CurrencyCode currCode);

Currency::CurrencyCode changeStringToEnum(std::string currCode);