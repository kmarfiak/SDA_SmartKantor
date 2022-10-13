#pragma once
#pragma once
#include <string>
#include "json.hpp"



namespace Zad
{
    using json = nlohmann::json;

    class Currency
    {
    public:
        Currency(std::string newCurrencyName, std::string newCodeName, float newBuyPrice, float newSellPrice)
            : currencyName(newCurrencyName), codeName(newCodeName), buyPrice(newBuyPrice), sellPrice(newSellPrice)
        {};


        std::string getCurrencyName() const //currencyTarget -> rename
        {
            return currencyName;
        }

        std::string getCodeName() const
        {
            return codeName;
        }

        float getBuyPrice() const
        {
            return buyPrice;
        }

        float getSellPrice() const
        {
            return sellPrice;
        }
              
        void setCurrencyName(std::string newCurrencyName)
        {
            currencyName = newCurrencyName;
        }

        void setCodeName(std::string newCodeName)
        {
            codeName = newCodeName;
        }

        void setBuyPrice(float newBuyPrice)
        {
            buyPrice = newBuyPrice;
        }

        void setSellPrice(float newSellPrice)
        {
            sellPrice = newSellPrice;
        }


    private:
        std::string currencyName;
        std::string codeName;
        float buyPrice;
        float sellPrice;
    };

    void to_json(json& j, const Currency& s);
    void from_json(const json& j, Currency& s);

}