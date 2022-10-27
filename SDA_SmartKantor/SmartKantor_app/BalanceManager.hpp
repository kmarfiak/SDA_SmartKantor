#pragma once
#include<map>
#include<string>

#include"Currency.hpp"


class BalanceManager
{
	std::map<Currency::CurrencyCode, float> balance;

public:
	BalanceManager();
	

	// wczytaj dostepne waluty z bazy danych
	bool readBalance();

	// zapisz stan wszystkich walut do bazy danych
	bool storeBalance();

	// najprawdopodobniej do usuniecia?, chyba, ze DisplayMenu bedzie pokazywalo wszystko jak leci
	std::map<Currency::CurrencyCode, float>& getBalance();
	
	// old: bool withdraw(float availableFunds, float value);
	bool withdraw(Currency::CurrencyCode code, float value);

	// old: void deposit(float availableFunds, float value);
	void deposit(Currency::CurrencyCode code, float value);

};


	
	