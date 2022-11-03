#pragma once
#include<map>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "curl/curl.h"
#include "json.hpp"

#include"Currency.hpp"

namespace
{
	std::size_t callback(
		const char* in,
		std::size_t size,
		std::size_t num,
		std::string* out)
	{
		const std::size_t totalBytes(size * num);
		out->append(in, totalBytes);
		return totalBytes;
	}
}

class TempRatesRetriever
{
	std::map<Currency::CurrencyCode, Currency> rates;

public:
	TempRatesRetriever()
	{
		Currency eur("euro", "EUR", 4.82f, 4.91f);
		Currency usd("dolar", "USD", 4.99f, 5.00f);
		Currency gbp("funt", "GBP", 5.53f, 5.64f);
		Currency chf("frank", "CHF", 4.91f, 5.01f);
		rates[Currency::CurrencyCode::EUR] = eur;
		rates[Currency::CurrencyCode::USD] = usd;
		rates[Currency::CurrencyCode::GBP] = gbp;
		rates[Currency::CurrencyCode::CHF] = chf;

	}

	std::map<Currency::CurrencyCode, Currency>& getRates() {
		return rates;
	}

	void retrieve()
	{
		//const std::string url("http://date.jsontest.com/");
		const std::string url("http://api.nbp.pl/api/exchangerates/tables/c/?format=json");

		CURL* curl = curl_easy_init();

		// Set remote URL.
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Don't bother trying IPv6, which would increase DNS resolution time.
		curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

		// Don't wait forever, time out after 10 seconds.
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

		// Follow HTTP redirects if necessary.
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		// Response information.
		long httpCode(0);
		std::unique_ptr<std::string> httpData(new std::string());

		// Hook up data handling function.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

		// Hook up data container (will be passed as the last parameter to the
		// callback handling function).  Can be any pointer type, since it will
		// internally be passed as a void pointer.
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

		// Run our HTTP GET command, capture the HTTP response code, and clean up.
		curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(curl);

		using json = nlohmann::json;

		if (httpCode == 200)
		{
			std::cout << "\nSuccessful response from NBP " << url << std::endl;
			//std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;

			//std::cout << std::setw(4) << j;
			std::ofstream o("currency.json");
			o << std::setw(4) << *httpData.get() << std::endl;
			json jf = json::parse(*httpData.get());

			for (auto& el : jf.items())
			{
				nlohmann::json object = el.value();
				std::cout << "\nGetting trading date: " << object.at("tradingDate") << std::endl;
				std::cout << "Getting publication date: " << object.at("effectiveDate") << std::endl;
				std::cout << "  " << std::endl;
			}

			for (auto& el : jf.items())
			{
				nlohmann::json object = el.value();

				for (auto& rate : object.at("rates"))
				{
					Currency curr(rate["currency"], rate["code"], rate["bid"], rate["ask"]);
					rates.emplace(std::make_pair(changeStringToEnum(rate["code"]), curr));
				}
			}
		}
		else
		{
			std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
		}
	}
};