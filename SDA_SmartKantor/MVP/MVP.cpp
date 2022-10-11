#include <iostream>
#include<map>

int main()
{
	std::map<std::string, float> balanceCurrency{ {"PLN", 765}, {"USD", 100}, {"GBP", 100} };

	void printBalance(std::map<std::string, float> balanceCurrency);
	{
		for (auto const& pair : balanceCurrency)
		{
			std::cout << "{" << pair.first << ": " << pair.second << "}" << std::endl;
		}
	}

}