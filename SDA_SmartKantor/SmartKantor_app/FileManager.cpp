#include "FileManager.hpp"
#include "TempRatesRetriever.hpp"
#include <string>
#include <sstream>

void FileManager::manageFilesReports()
{
    std::ofstream myWriteFile("reports.txt");
    myWriteFile.close();
}

void FileManager::save(Currency::CurrencyCode currCode, float amount, float value, std::string type)
{
    std::fstream myWriteFile;

    myWriteFile.open("reports.txt", std::ios::app);
    if (!myWriteFile) {
        manageFilesReports();
    }
    std::string dtstring = dt;
    std::stringstream ssAmount;
    ssAmount << std::fixed << std::setprecision(2) << amount;
    std::stringstream ssValue;
    ssValue << std::fixed << std::setprecision(2) << value;
    std::string
        str = "data transakcji: " + dtstring + "  ilosc: " + ssAmount.str() +
        "  wartosc: " + ssValue.str() + "PLN " + "waluta: " + currCode + " typ transakcji : " + type;
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
    myWriteFile << str << '\n';
    myWriteFile.close();
}

std::vector<std::string> FileManager::readReport()
{
    // ifstream jest do wczytywania, std::ios::in do odczytu
    std::ifstream reportFile("reports.txt", std::ios::in);
    std::vector<std::string> reportVector;

    if (!reportFile.is_open()) {
        std::cout << "Nie udalo sie otworzyc pliku" << "reports.txt" << '\n';
    }
    else 
    {
        // petla w ktorej kazda linijka pliku bedzie odczytywana az getline zwroci false (bedzie koniec pliku)
        for (std::string textLine; std::getline(reportFile, textLine); )
        {
            reportVector.push_back(textLine);
        }
    }
    return reportVector;
}

void FileManager::manageRatesReports()
{
    std::ofstream myWriteFile("rates.txt");
    myWriteFile.close();
}

void FileManager::saveRates()
{
    std::fstream myWriteFile;

    myWriteFile.open("rates.txt", std::ios::app);
    if (!myWriteFile) {
        manageRatesReports();
    }

    TempRatesRetriever temprates2;
    temprates2.retrieve();

    std::map<Currency::CurrencyCode, Currency> ratesMapa = temprates2.getRates();

    std::map<Currency::CurrencyCode, Currency>::iterator itr;
    std::string dtstring = dt;
    myWriteFile << "Kursy z dnia: " + dtstring << '\n';
    
        for (itr = ratesMapa.begin(); itr != ratesMapa.end(); itr++)
        {
            myWriteFile << itr->second << '\n';
        }
    
    myWriteFile.close();


}



