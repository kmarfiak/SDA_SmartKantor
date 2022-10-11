#pragma once
#include<string>


class BalanceManager
{
	bool withdraw(int amount, std::string currency);
	void deposit(int amount, std::string currency);

	//metody, ktore aktualizuja balance, odejmuja (withdraw) i dodaja (deposit)
	//pobieraja dane z plikow json, dodaja lub odejmuja te kwote, ktora klient chce wymienic i znow zapisuja dane do json
	//przy withdraw jest bool, bo dobrze jakby sprawdzilo czy jest tyle kasy by odjac
};

