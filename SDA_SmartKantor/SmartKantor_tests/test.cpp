#include "pch.h"
#include "../SmartKantor_app/Currency.hpp"
#include "../SmartKantor_app/Converter.hpp"
#include "../SmartKantor_app/BalanceManager.hpp"
TEST(CalculateBuyTest, CorrectCalculation)
{
	Converter convert1;
	EXPECT_FLOAT_EQ(convert1.calculateBuy(10, Currency::CurrencyCode::EUR), 49.169998);
}
TEST(CalculateBuyTest, InCorrectCalculation)
{
	Converter convert1;
	EXPECT_FLOAT_EQ(convert1.calculateBuy(10, Currency::CurrencyCode::EUR), 89.169998);
}
TEST(CalculateSellTest, CorrectCalculation)
{
	Converter convert1;
	EXPECT_FLOAT_EQ(convert1.calculateSell(10, Currency::CurrencyCode::EUR), 48.119999);
}
TEST(CalculateSellTest, InCorrectCalculation)
{
	Converter convert1;
	EXPECT_EQ(convert1.calculateSell(10, Currency::CurrencyCode::EUR), 67.093212);
}
TEST(CalculateBuyTest, CalculationAmount0)
{
	Converter convert1;
	EXPECT_EQ(convert1.calculateBuy(0, Currency::CurrencyCode::EUR), 0);
}
TEST(BalanceManagerWithdrawTest, BalanceLowerThanValue)
{
	BalanceManager balance1;
	ASSERT_THROW(balance1.withdraw(Currency::CurrencyCode::EUR, 6000), std::out_of_range);
}
TEST(BalanceManagerWithdrawTest, BalanceCorrectEdgeCase)
{
	BalanceManager balance1;
	EXPECT_EQ(balance1.withdraw(Currency::CurrencyCode::EUR, 5000), true);
}
TEST(BalanceManagerWithdrawTest, BalanceCorrectWithdraw)
{
	BalanceManager balance1;
	EXPECT_EQ(balance1.withdraw(Currency::CurrencyCode::EUR, 10), true);
}







