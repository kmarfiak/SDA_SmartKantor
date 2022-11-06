#include "DisplayMenu.hpp"
#include "ConGui/ConGui.h"
#include "Cashier.hpp"
#include <sstream>

// definicja konstruktora kt�ra przyjmuje referencje do obiektu cashier i przekazuje j� do pola klasy
DisplayMenu::DisplayMenu(Cashier& cashier)
    : _cashierRef(cashier) {}

void DisplayMenu::mainMenu()
{
    // zmienna do kt�rej wrzucamy wiadomo�ci do wy�wietlenia pod menu
    // np. wymieniono 20EUR za 100PLN lub z�apane wyj�tki, na pocz�tku puste
    std::string lastDisplayedMessage = "";

    // ustawienia pocz�tkowe ConGui
    SetConsoleTitleA("SmartKantor - wymiana walut");
    ConGui::ApplyConsoleStyle(20, L"Consolas");
    ConGui::SetWindow(140, 60, false, true);
    ConGui::Init();
    ConGui::SetCursorState(false);

    // zmienna typu enum kt�ra s�u�y do wyboru wy�wietlanego menu w p�tli poni�ej
    //na pocz�tku ustawiona na MainMenu
    Menu menu = Menu::MainMenu;
    // flaga s�u��ca do zako�czenia p�tli, tylko ExitOption ustawia ja na true i wychodzimy z p�tli
    bool exit = false;
    // zmienna trzymajaca kwote podawana przez u�ytkownika
    std::string amount = "";
    // zmienna przetrzymujaca rodzaj operacji przy wymianie waluty, uzupelni ja metoda subMenuAMount
    // (MenuBuy ustawi zmienna na kupic, Menu Sell na sprzedac)
    std::string operationType = "";
    // enum przechowuj�cy walut� do wymiany, ustawiany w subMenu
    Currency::CurrencyCode currCode;

    while (!exit)
    {
        // ustawienia ConGui
        ConGui::Style::ThemeBlue();
        Sleep(1);
        ConGui::Frame();
        ConGui::InputHandle();

        // wyb�r konkretnego menu do wy�wietlenia i opcja wyj�cia
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
        // tu metoda ConGui s�u�aca do od�wie�ania (rysuje elementy przy ka�dym obiegu p�tli)
        ConGui::Render();
    }
}

void DisplayMenu::initialMenu(std::string& lastDisplayedMessage, Menu& menu)
{
    // tytu� okienka
    std::string textToDisplay = "Witamy w SmartKantor";
    // ustawienia okienka
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    // rysowanie tekstu tytu�owego na �rodku okna i zamienienie stringa textToDisplay na char bo tego wymaga ConGui
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    // zmienne pomocnicze do ustawienia szeroko�ci przycisk�w, tak �eby by�y na �rodku okna
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    // kolejne przyciski z funkcjami kantora, ich zadaniem jest zmiana wyswietlanego menu
    //w kolejnym obiegu p�tli (wciskamy przycisk, podmieniamy enuma i zaczynamy znowu wyswietlac)
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
    // w tym miejscu wy�wietlana jest ostatnia wiadomo�� z systemu (dok�adny opis by� wy�ej)
    ConGui::Text((ConGui::ConsoleWidth / 2) - (lastDisplayedMessage.length() / 2) - 1, 28, lastDisplayedMessage.c_str());
}

// menu do wy�wietlania stanu kasy
void DisplayMenu::subMenuBalance(std::string& lastDisplayedMessage, Menu& menuRef)
{
    // pobranie mapy ze stanem kasy -> wywo�anie metody getBalance z Cashier
    // kopiujemy mape zeby nie naruszyc orygina�u z BalanceManagera
    std::map <Currency::CurrencyCode, float> balanceMap = _cashierRef.getBalance();

    // zmienne pomocnicze do ustawiania kolejno pozycji przycisk�w
    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
   
    // tu workaround do zamazywania pozosta�o�ci poprzednich menu, taki "urok" ConGui
    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualny stan kasy";

    // ustawienia okna i wy�wietlanych napis�w
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    // iterowanie po kolejnych elementach mapy przy uzyciu range based for
    for (auto element : balanceMap)
    {
        // do zmiennej pomocniczej currCodeSTring wpychamy kod waluty i ilo�� got�wki
        // kluczem w mapie jest CurrencyCode ktory trzeba zamienic na stringa (changeEnumToStrig),
        // podobnie trzeba zrobi� z floatem (amount) za pomoca std::to_string
        std::string currCodeString = changeEnumToString(element.first) + " | " + std::to_string(element.second);

        // box to obramowanie tekstu, ponizej ustawienia tak zeby sie ladnie wyswietla�o
        ConGui::Box((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) -3, (distanceBetweenText -1), 
                    (ConGui::ConsoleWidth / 2) + (currCodeString.length() / 2) + 2, (distanceBetweenText + 1));
        // wypisanie tekstu wewn�trz boxa 
        ConGui::Text((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) - 1, distanceBetweenText, currCodeString.c_str());
        // odst�py po wygenerowaniu kolejnego wiersza
        distanceBetweenText += 3;
    }
    // wyjscie do MainMenu
    if (ConGui::Button("Wyjdz", buttonXStartPosition, (distanceBetweenText - 1), buttonXStopPosition, (distanceBetweenText + 1), true))
    {
        menuRef = Menu::MainMenu;
    }
}

// wy�wietlanie raport�w
void DisplayMenu::reportsMenu(std::string& lastDisplayedMessage, Menu& menuRef)
{
    // zmienna pomocnicza, wektor przechowuje kolejne linie raportu do wy�wietlenia
    std::vector<std::string> reportToDisplay;

    // pobranie raportu do wektora za pomoc� wywo�ania funkcji getReport w Cashierze
    reportToDisplay = _cashierRef.getReport();

    // zmienne pomocnicze do ustawiania pozycji element�w
    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    // tu workaround do zamazywania pozosta�o�ci poprzednich menu, taki "urok" ConGui
    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualny raport- wszystkie transakcje";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());
    
    // p�tla do wy�wietlania kolejnych linii raportu z wektora
    for (auto element : reportToDisplay)
    {
        // bierzemy pojedynczy string jako reportLine
        std::string reportLine = element;
        
        // box to ramka, text to linia raportu, funkcja c_str do przerobienia stringa na chary ;)
        ConGui::Box(1, (distanceBetweenText - 1), ConGui::ConsoleWidth - 2, (distanceBetweenText + 1));
        ConGui::Text(2, distanceBetweenText, reportLine.c_str());
        distanceBetweenText += 3;
    }

    if (ConGui::Button("Wyjdz", buttonXStartPosition, (distanceBetweenText - 1), buttonXStopPosition, (distanceBetweenText + 1), true))
    {
        menuRef = Menu::MainMenu;
    }
}

// wyswietlenie aktualnych kurs�w
void DisplayMenu::ratesMenu(std::string& lastDisplayedMessage, Menu& menuRef)

{
    // kopia mapy z kursami walut
    std::map <Currency::CurrencyCode, Currency> ratesMap = _cashierRef.getRates();

    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    // j.w 
    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualne kursy";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    // pierwszy wiersz tabeli kurs�w
    std::string ratesInfoDisplay = "Nazwa waluty | Kod waluty | Kupno | Sprzedaz";
    // ustawienia ramki (box) i tekst w �rodku
    ConGui::Box((ConGui::ConsoleWidth / 2) - (ratesInfoDisplay.length() / 2) - 3, (distanceBetweenText - 1), (ConGui::ConsoleWidth / 2) + (ratesInfoDisplay.length() / 2) + 2, (distanceBetweenText + 1));
    ConGui::Text((ConGui::ConsoleWidth / 2) - (ratesInfoDisplay.length() / 2) - 1, distanceBetweenText, ratesInfoDisplay.c_str());
    distanceBetweenText += 3;

    // p�tla do wy�wietlania kolejnych element�w mapy
    for (auto element : ratesMap)
    {
        // do currCodeString wsadzamy poszczeg�lne elementy mapy
        // getCurrencyTarget to nazwa waluty
        // changeEnumToString jest metoda (w Currency.hpp) zamieniajaca enumy (kod waluty) na stringi
        // poni�ej sa zmienne pomocnicze typu stringstream do wyswietlenia tylko 4 miejsc po przecinku

        std::stringstream ssBuyPrice;
        ssBuyPrice << std::fixed << std::setprecision(4) << element.second.getBuyPrice();

        std::stringstream ssSellPrice;
        ssSellPrice << std::fixed << std::setprecision(4) << element.second.getSellPrice();

        std::string currCodeString = element.second.getCurrencyTarget() + " | " + changeEnumToString(element.first)
            + " | " + ssBuyPrice.str() + " | " + ssSellPrice.str();

        // j.w ramka i tekst
        ConGui::Box((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) - 3, (distanceBetweenText - 1), 
                    (ConGui::ConsoleWidth / 2) + (currCodeString.length() / 2) + 2, (distanceBetweenText + 1));
        ConGui::Text((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) - 1, distanceBetweenText, currCodeString.c_str());
        distanceBetweenText += 3;
    }

    //wyjscie
    if (ConGui::Button("Wyjdz", buttonXStartPosition, (distanceBetweenText - 1), buttonXStopPosition, (distanceBetweenText + 1), true))
    {
        menuRef = Menu::MainMenu;
    }
}

// menu kupna lub sprzeda�y zrobione jako jedno bo oba wygl�da�y identycznie
// zmienia� si� tylko tekst kupna i sprzeda�y
void DisplayMenu::subMenu(std::string operationType, Currency::CurrencyCode& currCode, Menu& menuRef)
{
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13; 
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
    // napis do wywietlenia w zaleznosci od operationType (switch w main menu)
    std::string textToDisplay = "Jaka walute chcesz " + operationType + "?";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    // mapa trzymajaca kursy pobrana z TempRates (ale wywo�ana przez cashiera)
    std::map<Currency::CurrencyCode, Currency>& ratesMap = _cashierRef.getRates();

    short int distanceBetweenButtons = 5;

    // p�tla generuj�ca przyciski dla ka�dej dost�pnej waluty
    for (auto element : ratesMap)
    {
        // rysowanie przycisku dla pojedynczej waluty poprzez wyciaganie elementu z obiektu Currency (getCurrencyCode)
        // i zamienianie go na char (c_str)
        if (ConGui::Button(element.second.getCurrencyCode().c_str(), buttonXStartPosition, distanceBetweenButtons, 
                           buttonXStopPosition, distanceBetweenButtons+2, true))
        {
            // ustawienie zmiennej currCode na klucz mapy (enum currency code)
            currCode = element.first;
            // przejscie do menu gdzie jest mozliwe podanie kwoty do wymiany
            menuRef = Menu::MenuAmount;
        }
        distanceBetweenButtons += 3;
    }

    if (ConGui::Button("Wyjdz", buttonXStartPosition, distanceBetweenButtons, buttonXStopPosition, distanceBetweenButtons + 2, true))
    {
        menuRef = Menu::MainMenu;
    }
}

std::string roundFloat(float number)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << number;
    std::string s = stream.str();
    return s;
}
// menu do pobrania ilo�ci waluty do wymiany
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

    // wyswietlenie okienka do podania ilosci gotowki i wartosc z tego okienka jest przekazywana do amount
    ConGui::InputText("Podaj ilosc:", (ConGui::ConsoleWidth / 2) - 18, 3, 26, 144, &amount, true, false);

    // jezeli wcisniemy wymien to wejdziemy do wnetrza if'a
    if (ConGui::Button("Wymien", buttonXStartPosition, 5, buttonXStopPosition, 7, true))
    {
        ConGui::Fill(ConGui::Style::MainColor);

        // przechwycenie wyjatku ktory mo�e by� zwr�cony z metody buy lub sell
        try
        {
            if (operationType == "kupic")
            {
                // je�eli kwota jest wi�ksza od 0 to dokonaj wymiany
                if (std::stof(amount) > 0)
                {
                    float amountToCalcBuy = _cashierRef.buy(currCode, std::stof(amount));
                    std::string s = roundFloat(amountToCalcBuy);
                    lastDisplayedMessage = "Kupiono " + amount + " " + currCode + " za " + s + " PLN. ";
                }
                else
                {
                    //rzucenie komunikatu z b��dem
                    lastDisplayedMessage = "Wprowadzono bledna kwote. Prosze podac kwote wieksza od zera.";
                }
            }
            else if (operationType == "sprzedac")
            {
                // tu jak wy�ej
                if (std::stof(amount) > 0)
                {
                    float amountToCalcSell = _cashierRef.sell(currCode, std::stof(amount));
                    std::string s = roundFloat(amountToCalcSell);
                    lastDisplayedMessage = "Sprzedano " + amount + " " + currCode + " za " + s + " PLN. ";
                }
                else
                {
                    lastDisplayedMessage = "Wprowadzono bledna kwote. Prosze podac kwote wieksza od zera.";
                }
            }
        }
        // �apanie wyjatk�w je�eli nie uda si� buy/sell lub stof (string to float)
        // invalid argument to jesli w amount ktos poda� tekst
        catch(std::invalid_argument&)
        {
            lastDisplayedMessage = "Wprowadzono nieprawidlowa wartosc. Prosze podac kwote do wymiany.";
        }
        // out of range jest rzucane z buy/sell gdy mamy za du�� kwot� do wymiany (BalanceMenager metoda withdraw)
        catch (std::out_of_range& exception)
        {
            // wy�wietlenie tekstu podanego w throw w BalanceManagerze
            lastDisplayedMessage = exception.what();
        }
        //wyzerowanie kwoty
        amount = "";
        // powr�t do g��wnego menu
        menuRef = Menu::MainMenu;
    }
    else if (ConGui::Button("Wyjdz", buttonXStartPosition, 8, buttonXStopPosition, 10, true))
    {
        ConGui::Fill(ConGui::Style::MainColor);
        menuRef = Menu::MainMenu;
    }
}
