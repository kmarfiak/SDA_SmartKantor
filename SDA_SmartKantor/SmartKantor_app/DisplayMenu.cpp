#include "DisplayMenu.hpp"
#include "ConGui/ConGui.h"
#include "Cashier.hpp"
#include <sstream>

// definicja konstruktora która przyjmuje referencje do obiektu cashier i przekazuje j¹ do pola klasy
DisplayMenu::DisplayMenu(Cashier& cashier)
    : _cashierRef(cashier) {}

void DisplayMenu::mainMenu()
{
    // zmienna do której wrzucamy wiadomoœci do wyœwietlenia pod menu
    // np. wymieniono 20EUR za 100PLN lub z³apane wyj¹tki, na pocz¹tku puste
    std::string lastDisplayedMessage = "";

    // ustawienia pocz¹tkowe ConGui
    SetConsoleTitleA("SmartKantor - wymiana walut");
    ConGui::ApplyConsoleStyle(20, L"Consolas");
    ConGui::SetWindow(140, 60, false, true);
    ConGui::Init();
    ConGui::SetCursorState(false);

    // zmienna typu enum która s³u¿y do wyboru wyœwietlanego menu w pêtli poni¿ej
    //na pocz¹tku ustawiona na MainMenu
    Menu menu = Menu::MainMenu;
    // flaga s³u¿¹ca do zakoñczenia pêtli, tylko ExitOption ustawia ja na true i wychodzimy z pêtli
    bool exit = false;
    // zmienna trzymajaca kwote podawana przez u¿ytkownika
    std::string amount = "";
    // zmienna przetrzymujaca rodzaj operacji przy wymianie waluty, uzupelni ja metoda subMenuAMount
    // (MenuBuy ustawi zmienna na kupic, Menu Sell na sprzedac)
    std::string operationType = "";
    // enum przechowuj¹cy walutê do wymiany, ustawiany w subMenu
    Currency::CurrencyCode currCode;

    while (!exit)
    {
        // ustawienia ConGui
        ConGui::Style::ThemeBlue();
        Sleep(1);
        ConGui::Frame();
        ConGui::InputHandle();

        // wybór konkretnego menu do wyœwietlenia i opcja wyjœcia
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
        // tu metoda ConGui s³u¿aca do odœwie¿ania (rysuje elementy przy ka¿dym obiegu pêtli)
        ConGui::Render();
    }
}

void DisplayMenu::initialMenu(std::string& lastDisplayedMessage, Menu& menu)
{
    // tytu³ okienka
    std::string textToDisplay = "Witamy w SmartKantor";
    // ustawienia okienka
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    // rysowanie tekstu tytu³owego na œrodku okna i zamienienie stringa textToDisplay na char bo tego wymaga ConGui
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    // zmienne pomocnicze do ustawienia szerokoœci przycisków, tak ¿eby by³y na œrodku okna
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    // kolejne przyciski z funkcjami kantora, ich zadaniem jest zmiana wyswietlanego menu
    //w kolejnym obiegu pêtli (wciskamy przycisk, podmieniamy enuma i zaczynamy znowu wyswietlac)
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
    // w tym miejscu wyœwietlana jest ostatnia wiadomoœæ z systemu (dok³adny opis by³ wy¿ej)
    ConGui::Text((ConGui::ConsoleWidth / 2) - (lastDisplayedMessage.length() / 2) - 1, 28, lastDisplayedMessage.c_str());
}

// menu do wyœwietlania stanu kasy
void DisplayMenu::subMenuBalance(std::string& lastDisplayedMessage, Menu& menuRef)
{
    // pobranie mapy ze stanem kasy -> wywo³anie metody getBalance z Cashier
    // kopiujemy mape zeby nie naruszyc orygina³u z BalanceManagera
    std::map <Currency::CurrencyCode, float> balanceMap = _cashierRef.getBalance();

    // zmienne pomocnicze do ustawiania kolejno pozycji przycisków
    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;
   
    // tu workaround do zamazywania pozosta³oœci poprzednich menu, taki "urok" ConGui
    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualny stan kasy";

    // ustawienia okna i wyœwietlanych napisów
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());

    // iterowanie po kolejnych elementach mapy przy uzyciu range based for
    for (auto element : balanceMap)
    {
        // do zmiennej pomocniczej currCodeSTring wpychamy kod waluty i iloœæ gotówki
        // kluczem w mapie jest CurrencyCode ktory trzeba zamienic na stringa (changeEnumToStrig),
        // podobnie trzeba zrobiæ z floatem (amount) za pomoca std::to_string
        std::string currCodeString = changeEnumToString(element.first) + " | " + std::to_string(element.second);

        // box to obramowanie tekstu, ponizej ustawienia tak zeby sie ladnie wyswietla³o
        ConGui::Box((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) -3, (distanceBetweenText -1), 
                    (ConGui::ConsoleWidth / 2) + (currCodeString.length() / 2) + 2, (distanceBetweenText + 1));
        // wypisanie tekstu wewn¹trz boxa 
        ConGui::Text((ConGui::ConsoleWidth / 2) - (currCodeString.length() / 2) - 1, distanceBetweenText, currCodeString.c_str());
        // odstêpy po wygenerowaniu kolejnego wiersza
        distanceBetweenText += 3;
    }
    // wyjscie do MainMenu
    if (ConGui::Button("Wyjdz", buttonXStartPosition, (distanceBetweenText - 1), buttonXStopPosition, (distanceBetweenText + 1), true))
    {
        menuRef = Menu::MainMenu;
    }
}

// wyœwietlanie raportów
void DisplayMenu::reportsMenu(std::string& lastDisplayedMessage, Menu& menuRef)
{
    // zmienna pomocnicza, wektor przechowuje kolejne linie raportu do wyœwietlenia
    std::vector<std::string> reportToDisplay;

    // pobranie raportu do wektora za pomoc¹ wywo³ania funkcji getReport w Cashierze
    reportToDisplay = _cashierRef.getReport();

    // zmienne pomocnicze do ustawiania pozycji elementów
    short int distanceBetweenText = 5;
    short int buttonXStartPosition = ConGui::ConsoleWidth / 2 - 13;
    short int buttonXStopPosition = ConGui::ConsoleWidth / 2 + 13;

    // tu workaround do zamazywania pozosta³oœci poprzednich menu, taki "urok" ConGui
    ConGui::Fill(ConGui::Style::MainColor);

    std::string textToDisplay = "Aktualny raport- wszystkie transakcje";

    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Combo;
    ConGui::Box(0, 0, ConGui::ConsoleWidth - 1, ConGui::ConsoleHeight - 1);
    ConGui::Style::BoxStyle = ConGui::Style::BoxStyle_Default;
    ConGui::Text((ConGui::ConsoleWidth / 2 - textToDisplay.length() / 2), 0, textToDisplay.c_str());
    
    // pêtla do wyœwietlania kolejnych linii raportu z wektora
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

// wyswietlenie aktualnych kursów
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

    // pierwszy wiersz tabeli kursów
    std::string ratesInfoDisplay = "Nazwa waluty | Kod waluty | Kupno | Sprzedaz";
    // ustawienia ramki (box) i tekst w œrodku
    ConGui::Box((ConGui::ConsoleWidth / 2) - (ratesInfoDisplay.length() / 2) - 3, (distanceBetweenText - 1), (ConGui::ConsoleWidth / 2) + (ratesInfoDisplay.length() / 2) + 2, (distanceBetweenText + 1));
    ConGui::Text((ConGui::ConsoleWidth / 2) - (ratesInfoDisplay.length() / 2) - 1, distanceBetweenText, ratesInfoDisplay.c_str());
    distanceBetweenText += 3;

    // pêtla do wyœwietlania kolejnych elementów mapy
    for (auto element : ratesMap)
    {
        // do currCodeString wsadzamy poszczególne elementy mapy
        // getCurrencyTarget to nazwa waluty
        // changeEnumToString jest metoda (w Currency.hpp) zamieniajaca enumy (kod waluty) na stringi
        // poni¿ej sa zmienne pomocnicze typu stringstream do wyswietlenia tylko 4 miejsc po przecinku

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

// menu kupna lub sprzeda¿y zrobione jako jedno bo oba wygl¹da³y identycznie
// zmienia³ siê tylko tekst kupna i sprzeda¿y
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

    // mapa trzymajaca kursy pobrana z TempRates (ale wywo³ana przez cashiera)
    std::map<Currency::CurrencyCode, Currency>& ratesMap = _cashierRef.getRates();

    short int distanceBetweenButtons = 5;

    // pêtla generuj¹ca przyciski dla ka¿dej dostêpnej waluty
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
// menu do pobrania iloœci waluty do wymiany
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

        // przechwycenie wyjatku ktory mo¿e byæ zwrócony z metody buy lub sell
        try
        {
            if (operationType == "kupic")
            {
                // je¿eli kwota jest wiêksza od 0 to dokonaj wymiany
                if (std::stof(amount) > 0)
                {
                    float amountToCalcBuy = _cashierRef.buy(currCode, std::stof(amount));
                    std::string s = roundFloat(amountToCalcBuy);
                    lastDisplayedMessage = "Kupiono " + amount + " " + currCode + " za " + s + " PLN. ";
                }
                else
                {
                    //rzucenie komunikatu z b³êdem
                    lastDisplayedMessage = "Wprowadzono bledna kwote. Prosze podac kwote wieksza od zera.";
                }
            }
            else if (operationType == "sprzedac")
            {
                // tu jak wy¿ej
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
        // ³apanie wyjatków je¿eli nie uda siê buy/sell lub stof (string to float)
        // invalid argument to jesli w amount ktos poda³ tekst
        catch(std::invalid_argument&)
        {
            lastDisplayedMessage = "Wprowadzono nieprawidlowa wartosc. Prosze podac kwote do wymiany.";
        }
        // out of range jest rzucane z buy/sell gdy mamy za du¿¹ kwotê do wymiany (BalanceMenager metoda withdraw)
        catch (std::out_of_range& exception)
        {
            // wyœwietlenie tekstu podanego w throw w BalanceManagerze
            lastDisplayedMessage = exception.what();
        }
        //wyzerowanie kwoty
        amount = "";
        // powrót do g³ównego menu
        menuRef = Menu::MainMenu;
    }
    else if (ConGui::Button("Wyjdz", buttonXStartPosition, 8, buttonXStopPosition, 10, true))
    {
        ConGui::Fill(ConGui::Style::MainColor);
        menuRef = Menu::MainMenu;
    }
}
