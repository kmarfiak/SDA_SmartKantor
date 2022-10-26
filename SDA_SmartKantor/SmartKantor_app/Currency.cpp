#include <iostream>
#include <fstream>

#include "Currency.hpp"
//#include "json/json.hpp"


Currency::Currency(std::string currencyTarget, std::string codeName, float buyPrice, float sellPrice)
{
	this->currencyTarget = currencyTarget;
	this->codeName = codeName;
	this->buyPrice = buyPrice;
	this->sellPrice = sellPrice;
}

Currency::Currency()
{
}

float Currency::getBuyPrice()
{
	return buyPrice;
}
void Currency::setBuyPrice(float buyPrice)
{
	this->buyPrice = buyPrice;
}
float Currency::getSellPrice()
{
	return sellPrice;
}
void Currency::setSellPrice(float sellPrice)
{
	this->sellPrice = sellPrice;
}
std::string Currency::getCurrencySource()
{
	return currencySource;
}
std::string Currency::getCurrencyTarget()
{
    return currencyTarget;
}
std::string Currency::getCurrencyCode()
{
	return codeName;
}
void Currency::setCurrencySource(std::string currencySource)
{
	this->currencySource = currencySource;
}

// przerzucilam tu przeciazenia operatorow scisle zwiazane z klasa Currency (przydadza sie tez do wyswietlania stanu kasy z BalanceManagera)

std::ostream& operator<<(std::ostream& os, Currency::CurrencyCode currCode)
{
    return os << changeEnumToString(currCode);
}

std::string operator+(std::string str, Currency::CurrencyCode currCode)
{
    return str + changeEnumToString(currCode);
}

std::string changeEnumToString(Currency::CurrencyCode currCode)
{
    switch (currCode)
    {
    case Currency::CurrencyCode::CHF:
        return "CHF";
        break;
    case Currency::CurrencyCode::EUR:
        return "EUR";
        break;
    case Currency::CurrencyCode::GBP:
        return "GBP";
        break;
    case Currency::CurrencyCode::PLN:
        return "PLN";
        break;
    case Currency::CurrencyCode::USD:
        return "USD";
        break;
    }
}
