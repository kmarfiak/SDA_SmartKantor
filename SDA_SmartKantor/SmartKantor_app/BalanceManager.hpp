#pragma once
#include<map>
#include<string>

#include"Currency.h"


class BalanceManager
{
	std::map<Currency::CurrencyCode, float> balance;

public:
	BalanceManager()
	{
		readBalance();
	}

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


	
	//bool withdraw (Currency::CurrencyCode currCodeSource, float amount)
	//{
	//	std::map<Currency::CurrencyCode, txnAmount> rates;
	//	float wynik = amount * rates[currCodeSource].getBuyPrice();
	//	return wynik;

	////atrybuty
	//float depositAmount = 500.00;//ile mamy obcej waluty
	////float amount = 300.25; //ile chcemy kupiæ/sprzedaæ obcej waluty
	//float withdrawalAmount; //kwota po przeliczeniu jaka musimy wydaæ z kasy
	//float incomingAmount; //kwota jaka przyjmujemy do kasy w walucie od klienta

	//std::string command; //buy lub sell
	//std::string currency = "EUR"; //jaka to waluta

	////metody
	//bool withdraw(float amount, float depositAmount);
	//void deposit(float amount, float depositAmount);

	//metody, ktore aktualizuja balance, odejmuja (withdraw) i dodaja (deposit)
	//pobieraja dane z plikow json, dodaja lub odejmuja te kwote, ktora klient chce wymienic i znow zapisuja dane do json
	//przy withdraw jest bool, bo dobrze jakby sprawdzilo czy jest tyle kasy by odjac
