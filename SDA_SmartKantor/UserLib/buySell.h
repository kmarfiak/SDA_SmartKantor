//#pragma once
//
//class buySell
//{
//
//	float buy(int amount, std::string baseCurrency) {
//		bool success = balanceManager.withdraw(amount, baseCurrency);
//		if (!success) {
//			return 0;
//		}
//		else {
//			float quoteCurrency = exchange.calculateBuy(amount, baseCurrency);
//			balanceManager.deposit(quoteCurrency, "PLN");
//			return quoteCurrency;
//		}
//		//balance(baseCurrency) = balance(baseCurrency) - amount;
//
//		//balance("PLN") = balance("PLN") + quoteCurrency;
//	}
//
//	float sell(int amount, std::string baseCurrency) {
//		balance("PLN") = balance("PLN") - amount;
//		float quoteCurrency = exchange.calculateSell(amount, baseCurrency);
//		balance(baseCurrency) = balance(baseCurrency) + quoteCurrency;
//		return quoteCurrency;
//	}
//};
