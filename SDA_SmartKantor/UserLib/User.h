#pragma once
#include<string>
#include<vector>
#include<map>
#include "Currency.h"

class User
{
	virtual	float buy(int amount, std::string currency) = 0; //klient podaje ile chce kupic USD, metpda zwraca ile PLN ma dac
	virtual float sell(int amount, std::string currency) = 0;//klient podaje ile chce sprzedac np USD, metpda zwraca ile dostanie PLN
	virtual std::vector<Currency> getRates() = 0;
	virtual std::map<std::string, float> getBalance() = 0;

	virtual ~User();
};