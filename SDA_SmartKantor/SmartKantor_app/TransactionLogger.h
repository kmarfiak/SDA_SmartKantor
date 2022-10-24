#pragma once
#include "FileManager.h"
#include "Currency.hpp"
#include <ctime>

class TransactionLogger
{
public:

	FileManager fileManager1;

	void log(Currency::CurrencyCode currCode, float amount, float value, std::string type)
	{
		fileManager1.save(currCode, amount, value, type);
	}

};
