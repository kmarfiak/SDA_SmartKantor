#pragma once
#include<iostream>
#include"BalanceRetriever.h"


class FileBalanceRetriever :public BalanceRetriever
{
public:

	std::map<std::string, float> getBalance();
	void displayBalance(std::map<std::string, float> balanceJSON);

};