#pragma once
#include "FileManager.hpp"
#include "Currency.hpp"
#include <ctime>
#include <vector>

class TransactionLogger
{
public:
	FileManager fileManager1;

	void log(Currency::CurrencyCode currCode, float amount, float value, std::string type);
	// pobranie raportu odczytanego w FileManagerze
	std::vector<std::string> getReport();
};
