#include "FileBalanceRetriever.h"

std::map<std::string, float> FileBalanceRetriever::getBalance()
{
	std::map<std::string, float> balanceJSON = { {"PLN", 900},{"USD", 870},{"EUR", 500} };
	return balanceJSON;
}

void FileBalanceRetriever::displayBalance(std::map<std::string, float> balanceJSON)
{
	for (auto const& pair : balanceJSON)
	{
		std::cout << "{" << pair.first << ": " << pair.second << "}" << std::endl;
	}
}
\