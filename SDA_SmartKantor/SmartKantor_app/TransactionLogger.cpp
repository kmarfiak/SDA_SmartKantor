#include "TransactionLogger.hpp"

void TransactionLogger::log(Currency::CurrencyCode currCode, float amount, float value, std::string type)
{
	fileManager1.save(currCode, amount, value, type);
}

std::vector<std::string> TransactionLogger::getReport()
{
	return fileManager1.readReport();
}
