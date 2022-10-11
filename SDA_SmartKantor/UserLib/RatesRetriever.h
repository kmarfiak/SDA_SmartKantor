#pragma once
#include<vector>
#include"Currency.h"


class RatesRetriever
{
	virtual std::vector<Currency> getRates() = 0;
	virtual ~RatesRetriever();
	//implementacja odczytywania z pliku json
	//potrzebna bedzie implementacja getRates, ktora bedzie dane z pliku json wprowadzala do wektora

};
