#pragma once
#include<string>
//#include "json/json.hpp"


	class Currency
	{
		std::string currencyName;
		std::string codeName;
		float buyPrice;
		float sellPrice;
		std::string baseCurrency = "PLN";//czyli PLN
	public:
		Currency(std::string newCurrencyName, std::string newCodeName, float newBuyPrice, float newSellPrice);
		Currency();
		float getBuyPrice();
		void setBuyPrice(float newBuyPrice);
		float getSellPrice();
		void setSellPrice(float newSellPrice);
		std::string getBaseCurrency();
		void setBaseCurrency(std::string newBaseCurrency);
		//void to_json(json& j, const Currency& s);
		//void from_json(const json& j, Currency& s);
	};
