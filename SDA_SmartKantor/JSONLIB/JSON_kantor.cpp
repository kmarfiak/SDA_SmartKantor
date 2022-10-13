// JSON_kantor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Waluty.hpp"
#include "pch.h"


namespace Zad {
    using json = nlohmann::json;
      
    void to_json(json& j, const Currency& s)
    {
        j = json{ {"currencyName", s.getCurrencyName()}, {"codeName" , s.getCodeName()}, {"buyPrice" , s.getBuyPrice()}, {"sellPrice" , s.getSellPrice()} };
    }

    void from_json(const json& j, Currency& s)
    {
        s.setCurrencyName(j["currencyName"].get<std::string>());
        s.setCodeName(j["codeName"]);

        float buyPrice;
        j["buyPrice"].get_to(buyPrice); //get_to sluzy do porowniania zmiennej
        s.setBuyPrice(buyPrice);

        float sellPrice;
        j["sellPrice"].get_to(sellPrice);
        s.setSellPrice(sellPrice);

    }

}