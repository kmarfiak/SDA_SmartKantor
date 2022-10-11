#include <iostream>
#include <fstream>
#include "Currency.h"
#include "json/json.hpp"


float Currency::getBuyPrice()
{
	return buyPrice;
}
void Currency::setBuyPrice(float newBuyPrice)
{
	buyPrice = newBuyPrice;
}
float Currency::getSellPrice()
{
	return sellPrice;
}
void Currency::setSellPrice(float newSellPrice)
{
	sellPrice = newSellPrice;
}
std::string Currency::getBaseCurrency()
{
	return baseCurrency;
}
void Currency::setBaseCurrency(std::string newBaseCurrency)
{
	baseCurrency = newBaseCurrency;
}