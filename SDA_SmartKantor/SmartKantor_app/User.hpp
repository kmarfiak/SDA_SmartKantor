#pragma once
#include <iostream>
#include <string>

#include "Converter.h"

class User
{
public:
	
	Converter converter1;

	float buy(Currency::CurrencyCode currCodeSource, float amount);

	float sell(Currency::CurrencyCode currCodeSource, float amount);
};