#pragma once
#include "FileManager.hpp"
#include <ctime>

class RatesLogger
{
public:
	FileManager fileManager2;

	void logRates();
};
