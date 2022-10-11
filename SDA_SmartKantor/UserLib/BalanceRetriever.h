#pragma once

#include<map>
#include<string>

class BalanceRetriever
{
	virtual std::map<std::string, float> getBalance() = 0;
	virtual ~BalanceRetriever();
	//odczytywanie w pliku json, dane ktore beda w pliku json czyli ilosc kazdej waluty w kantorze
	//potrezbna bedzie implementacja getBalance, ktora bedzie dane z pliku json wprowadzala do mapy 
	//i zwraca te mape
};
