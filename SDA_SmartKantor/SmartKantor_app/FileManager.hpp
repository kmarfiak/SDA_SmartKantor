#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Currency.hpp"
#include <algorithm>
#include <vector>



class FileManager
{
public:


    time_t now = time(0); // get current dat/time with respect to system  

    char* dt = ctime(&now);

    void manageFilesReports();
    void save(Currency::CurrencyCode currCode, float amount, float value, std::string type);
    //odczytanie zapisanego raportu ktory zostanie przekazany TransactionLoggera
    std::vector<std::string> readReport();
    void manageRatesReports();
    void saveRates();
    
};

