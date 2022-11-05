#include "FileManager.hpp"

void FileManager::manageFiles()
{
    std::ofstream myWriteFile("reports.txt");
    myWriteFile.close();
}

void FileManager::save(Currency::CurrencyCode currCode, float amount, float value, std::string type)
{
    std::fstream myWriteFile;

    myWriteFile.open("reports.txt", std::ios::app);
    if (!myWriteFile) {
        manageFiles();
    }

    std::string dtstring = dt;
    std::string
        str = "data transakcji: " + dtstring + "  ilosc: " + std::to_string(amount) +
        "  wartosc: " + std::to_string(value) + "PLN " + "waluta: " + currCode + " typ transakcji : " + type;
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
