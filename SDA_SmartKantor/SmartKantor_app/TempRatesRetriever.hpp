#pragma once
#include<map>
#include"Currency.hpp"

class TempRatesRetriever

{
	std::map<Currency::CurrencyCode, Currency> rates;

public:
	TempRatesRetriever()
	{
	Currency eur("euro", "EUR", 4.82, 4.91);
	Currency usd("dolar", "USD", 4.99, 5.00);
	Currency gbp("funt", "GBP", 5.53, 5.64);
	Currency chf("frank", "CHF", 4.91, 5.01);
	rates[Currency::CurrencyCode::EUR] = eur;
	rates[Currency::CurrencyCode::USD] = usd;
	rates[Currency::CurrencyCode::GBP] = gbp;
	rates[Currency::CurrencyCode::CHF] = chf;

	}

	std::map<Currency::CurrencyCode, Currency>& getRates() {
		return rates;
	}

	void retrieve()
	{
		Currency huf("forint", "HUF", 1.82, 2.91);
		Currency jpy("jen japonski", "JPY", 2.99, 2.00);

		rates[Currency::CurrencyCode::HUF] = huf;
		rates[Currency::CurrencyCode::JPY] = jpy;
	}
};
