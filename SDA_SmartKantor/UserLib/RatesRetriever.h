#pragma once
#include<map>
#include"Currency.h"
#include "DisplayMenu.hpp"


class RatesRetriever
{
public:
	virtual std::map<Currency::CurrencyCode, Currency> getRates() = 0;
	virtual ~RatesRetriever();
	//implementacja odczytywania z pliku json
	//potrzebna bedzie implementacja getRates, ktora bedzie dane z pliku json wprowadzala do wektora

};
