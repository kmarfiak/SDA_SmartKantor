#include "DisplayMenu.hpp"
#include "ConGui/ConGui.h"
#include "Cashier.hpp"


DisplayMenu::DisplayMenu(Cashier& cashier)
    : _cashierRef(cashier) {}

void DisplayMenu::mainMenu()
{
    int choice = 0;
    std::string lastDisplayedMessage = "";

    SetConsoleTitleA("SmartKantor - wymiana walut");
    ConGui::ApplyConsoleStyle(20, L"Consolas");
    ConGui::SetWindow(140, 60, false, true);
    ConGui::Init();
    ConGui::SetCursorState(false);

    Menu menu = Menu::MainMenu;
    bool exit = false;
    std::string amount = "";
    std::string operationType = "";
    Currency::CurrencyCode currCode;

    while (!exit)
    {
        ConGui::Style::ThemeBlue();
        Sleep(1);
        ConGui::Frame();
        ConGui::InputHandle();

        switch (menu)
        {
        case Menu::MainMenu:
            initialMenu(lastDisplayedMessage, menu);
            break;
        case Menu::MenuBuy:
            operationType = "kupic";
            subMenu(operationType, currCode, menu);
            break;
        case Menu::MenuSell:
            operationType = "sprzedac";
            subMenu(operationType, currCode, menu);
            break;
        case Menu::MenuAmount:
            subMenuAmount(amount, currCode, operationType, lastDisplayedMessage, menu);
            break;
        case Menu::MenuBalance:
            subMenuBalance(lastDisplayedMessage, menu);
            break;
        case Menu::MenuReport:
            reportsMenu(lastDisplayedMessage, menu);
            break;
        case Menu::MenuRates:
            ratesMenu(lastDisplayedMessage, menu);
            break;
        case Menu::ExitOption:
            exit = true;
            break;
        }
        ConGui::Render();
    }
}

void DisplayMenu::initialMenu(std::string& lastDisplayedMessage, Menu& menu)
{
    std::string textToDisplay = "Witamy w SmartKantor";
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    if (ConGui::Button("Kupno", buttonXStartPosition, 5, buttonXStopPosition, 7, true))
    {
        menu = Menu::MenuBuy;
    }
    else if (ConGui::Button("Sprzedaz", buttonXStartPosition, 8, buttonXStopPosition, 10, true))
    {
        menu = Menu::MenuSell;
    }
    else if (ConGui::Button("Stan kasy", buttonXStartPosition, 11, buttonXStopPosition, 13, true))
    {
        menu = Menu::MenuBalance;
    }
    else if (ConGui::Button("Wyswietl aktualny raport", buttonXStartPosition, 14, buttonXStopPosition, 16, true))
    {
        menu = Menu::MenuReport;
    }
    else if (ConGui::Button("Aktualizuj kursy", buttonXStartPosition, 17, buttonXStopPosition, 19, true))
    {
        _cashierRef.updateRates();
    }
    else if (ConGui::Button("Wyswietl aktualne kursy", buttonXStartPosition, 20, buttonXStopPosition, 22, true))
    {
        menu = Menu::MenuRates;
    }
    else if (ConGui::Button("Wyjdz", buttonXStartPosition, 23, buttonXStopPosition, 25, true))
    {
        menu = Menu::ExitOption;
    }
    ConGui::Text((ConGui::ConsoleWidth / 2) - (lastDisplayedMessage.length() / 2) - 1, 28, lastDisplayedMessage.c_str());
}

void DisplayMenu::subMenuBalance(std::string& lastDisplayedMessage, Menu& menuRef)
{
    std::map <Currency::CurrencyCode, float> balanceMap = _cashierRef.getBalance();

    std::string currCodeString = "";
    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
   
    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualny stan kasy";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    for (auto element : balanceMap)
    {
        std::string currCodeString = changeEnumToString(element.first) + " | " + std::to_string(element.second);

        ConGui::Box((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) -3, (distanceBetweenText -1), 
                    (ConGui::ConsoleWidth / 2) + (currCodeString.length() / 2) + 2, (distanceBetweenText + 1));
        ConGui::Text((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) - 1, distanceBetweenText, currCodeString.c_str());
        distanceBetweenText += 3;
    }

    if (ConGui::Button("Wyjdz", buttonXStartPosition, (distanceBetweenText - 1), buttonXStopPosition, (distanceBetweenText + 1), true))
    {
        menuRef = Menu::MainMenu;
    }
}

void DisplayMenu::reportsMenu(std::string& lastDisplayedMessage, Menu& menuRef)
{
    std::vector<std::string> reportToDisplay;

    reportToDisplay = _cashierRef.getReport();

    
    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualny raport- wszystkie transakcje";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    for (auto element : reportToDisplay)
    {
        std::string reportLine = element;

        ConGui::Box(1, (distanceBetweenText - 1), ConGui::ConsoleWidth - 2, (distanceBetweenText + 1));
        ConGui::Text(2, distanceBetweenText, reportLine.c_str());
        distanceBetweenText += 3;
    }

    if (ConGui::Button("Wyjdz", buttonXStartPosition, (distanceBetweenText - 1), buttonXStopPosition, (distanceBetweenText + 1), true))
    {
        menuRef = Menu::MainMenu;
    }
}

void DisplayMenu::ratesMenu(std::string& lastDisplayedMessage, Menu& menuRef)
{
    std::map <Currency::CurrencyCode, Currency> ratesMap = _cashierRef.getRates();

    std::string currCodeString = "";
    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualne kursy";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    std::string ratesInfoDisplay = "Nazwa waluty | Kod waluty | Kupno | Sprzedaz";
    ConGui::Box((ConGui::ConsoleWidth / 2) - (ratesInfoDisplay.length() / 2) - 3, (distanceBetweenText - 1), (ConGui::ConsoleWidth / 2) + (ratesInfoDisplay.length() / 2) + 2, (distanceBetweenText + 1));
    ConGui::Text((ConGui::ConsoleWidth / 2) - (ratesInfoDisplay.length() / 2) - 1, distanceBetweenText, ratesInfoDisplay.c_str());
    distanceBetweenText += 3;

    for (auto element : ratesMap)
    {
        std::string currCodeString = element.second.getCurrencyTarget() + " | " + changeEnumToString(element.first)
            + " | " + std::to_string(element.second.getBuyPrice()) + " | " + std::to_string(element.second.getSellPrice());

        ConGui::Box((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) - 3, (distanceBetweenText - 1), 
                    (ConGui::ConsoleWidth / 2) + (currCodeString.length() / 2) + 2, (distanceBetweenText + 1));
        ConGui::Text((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) - 1, distanceBetweenText, currCodeString.c_str());
        distanceBetweenText += 3;
    }

    if (ConGui::Button("Wyjdz", buttonXStartPosition, (distanceBetweenText - 1), buttonXStopPosition, (distanceBetweenText + 1), true))
    {
        menuRef = Menu::MainMenu;
    }
}

void DisplayMenu::subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef)
{
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13; 
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
    std::string textToDisplay = "Jaka walute chcesz " + operationType + "?";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    std::map<Currency::CurrencyCode, Currency>& ratesMap = _cashierRef.getRates();

    short int distanceBetweenButtons = 5;
    for (auto element : ratesMap)
    {
        if (ConGui::Button(element.second.getCurrencyCode().c_str(), buttonXStartPosition, distanceBetweenButtons, 
                           buttonXStopPosition, distanceBetweenButtons+2, true))
        {
            currCode = element.first;
            menuRef = Menu::MenuAmount;
        }
        distanceBetweenButtons += 3;
    }

    if (ConGui::Button("Wyjdz", buttonXStartPosition, distanceBetweenButtons, buttonXStopPosition, distanceBetweenButtons + 2, true))
    {
        menuRef = Menu::MainMenu;
    }
}

void DisplayMenu::subMenuAmount(std::string& amount, Currency::CurrencyCode& currCode, std::string& operationType, 
                                std::string& lastDisplayedMessage, Menu& menuRef)
{
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
    std::string textToDisplay = "Wymiana waluty";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    ConGui::InputText("Podaj ilosc:", (ConGui::ConsoleWidth / 2) - 18, 3, 26, 144, &amount, true, false);

    if (ConGui::Button("Wymien", buttonXStartPosition, 5, buttonXStopPosition, 7, true))
    {
        ConGui::Fill(ConGui::Style::MainColor);

        try
        {
            if (operationType == "kupic")
            {
                if (std::stof(amount) > 0)
                {
                    float amountToCalcBuy = _cashierRef.buy(currCode, std::stof(amount));
                    std::cout << std::to_string(amountToCalcBuy);
                    lastDisplayedMessage = std::to_string(amountToCalcBuy);
                    //lastDisplayedMessage = "Kupiono " + amount + " " + currCode + " za " + std::to_string(amountToCalcBuy) + " PLN. ";
                }
                else
                {
                    lastDisplayedMessage = "Wprowadzono bledna kwote. Prosze podac kwote wieksza od zera.";
                }
            }
            else if (operationType == "sprzedac")
            {
                if (std::stof(amount) > 0)
                {
                    float amountToCalcSell = _cashierRef.sell(currCode, std::stof(amount));
                    lastDisplayedMessage = "Sprzedano " + amount + " " + currCode + " za " + std::to_string(amountToCalcSell) + " PLN. ";
                }
                else
                {
                    lastDisplayedMessage = "Wprowadzono bledna kwote. Prosze podac kwote wieksza od zera.";
                }
            }
        }
        catch(std::invalid_argument&)
        {
            lastDisplayedMessage = "Wprowadzono nieprawidlowa wartosc. Prosze podac kwote do wymiany.";
        }
        catch (std::out_of_range& exception)
        {
            lastDisplayedMessage = exception.what();
        }
        amount = "";
        menuRef = Menu::MainMenu;
    }
    else if (ConGui::Button("Wyjdz", buttonXStartPosition, 8, buttonXStopPosition, 10, true))
    {
        ConGui::Fill(ConGui::Style::MainColor);
        menuRef = Menu::MainMenu;
    }
}
