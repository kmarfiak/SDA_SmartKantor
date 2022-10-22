#include "DisplayMenu.hpp"
#include "ConGui/ConGui.h"
#include "User.hpp"


void DisplayMenu::subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef)
{
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13; 
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
    std::string textToDisplay = "Jaka walute chcesz " + operationType + "?";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text(ConGui::ConsoleWidth / 2 - 10, 0, textToDisplay.c_str());

    std::map<Currency::CurrencyCode, Currency>& ratesMap = _cashierRef.getRates();

    short int distanceBetweenButtons = 5;
    for (auto element : ratesMap)
    {
        if (ConGui::Button(element.second.getCurrencyCode().c_str(), buttonXStartPosition, distanceBetweenButtons, buttonXStopPosition, distanceBetweenButtons+2, true))
        {
            currCode = element.first;
            menuRef = Menu::MenuAmount;
        }
        distanceBetweenButtons += 3;
    }

    if (ConGui::Button("Wyjdz", buttonXStartPosition, 17, buttonXStopPosition, 19, true))
    {
        menuRef = Menu::MainMenu;
    }
}

void DisplayMenu::subMenuAmount(std::string& amount, Currency::CurrencyCode& currCode, std::string& operationType, std::string& lastDisplayedMessage, Menu& menuRef)
{
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
    std::string textToDisplay = "Wymiana waluty";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text(ConGui::ConsoleWidth / 2 - 10, 0, textToDisplay.c_str());

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
                    lastDisplayedMessage = "Kupiono " + amount + " " + currCode + " za " + std::to_string(amountToCalcBuy) + " PLN. ";
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
        catch(std::invalid_argument)
        {
            lastDisplayedMessage = "Wprowadzono nieprawidlowa wartosc. Prosze podac kwote do wymiany.";
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

void DisplayMenu::initialMenu(std::string& lastDisplayedMessage, Menu& menu)
{
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text(ConGui::ConsoleWidth / 2 - 10, 0, "Witamy w SmartKantor");

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
        lastDisplayedMessage = "Jeszcze nie wspierany";
    }
    else if (ConGui::Button("Aktualizuj kursy", buttonXStartPosition, 14, buttonXStopPosition, 16, true))
    {
        lastDisplayedMessage = "Jeszcze nie wspierany";
    }
    else if (ConGui::Button("Wyswietl aktualne kursy", buttonXStartPosition, 17, buttonXStopPosition, 19, true))
    {
        lastDisplayedMessage = "Jeszcze nie wspierany";
    }
    else if (ConGui::Button("Wyjdz", buttonXStartPosition, 20, buttonXStopPosition, 22, true))
    {
        menu = Menu::ExitOption;
    }
    ConGui::Text((ConGui::ConsoleWidth / 2) - (lastDisplayedMessage.length() / 2) -1, 25, lastDisplayedMessage.c_str());
}

DisplayMenu::DisplayMenu(Cashier& cashier)
    : _cashierRef(cashier)
{
}

void DisplayMenu::mainMenu()
{
    int choice = 0;
    std::string lastDisplayedMessage = "";

    SetConsoleTitleA("SmartKantor - wymiana walut");
    ConGui::ApplyConsoleStyle(20, L"Consolas");
    ConGui::SetWindow(100, 40, false, true);
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
        case Menu::ExitOption:
            exit = true;
            break;
        }
        ConGui::Render();
    }
}

