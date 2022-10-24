#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <TransactionLogger.h>
#include "Currency.hpp"
#include <algorithm>


class FileManager

{
public:

    time_t now = time(0); // get current dat/time with respect to system  

    char* dt = ctime(&now);

	void manageFiles()
    {
        std::ofstream myWriteFile("reports.txt");
        myWriteFile.close();
    }

    void save(Currency::CurrencyCode currCode, float amount, float value, std::string type)
    {

       std::fstream myWriteFile;

       myWriteFile.open("reports.txt", std::ios::app);
       if (!myWriteFile) {
           manageFiles();
       }

        std::string dtstring =  dt;
        std::string str = "data transakcji: " +  dtstring + "  ilosc: " + std::to_string(amount) + 
            "  wartosc: " + std::to_string(value) + "PLN " + "waluta: " + currCode + " typ transakcji : " + type;
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
        myWriteFile << str << '\n';
        myWriteFile.close();
    }

};

