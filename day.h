#ifndef DAY_H
#define DAY_H

#include "date.h"
#include <iostream>

using namespace std;

struct day {
	// PARAMETERIZED CONSTRUCTOR
	day(const date& today, unsigned totalDeaths, unsigned totalCases);
	// DATE OF THIS DAY
	date today;
	// TOTAL CUMULATIVE DEATHS UP TO THIS DATE
	unsigned totalDeaths;
	// NEW DEATHS (JUST THIS DAY)
	unsigned newDeaths = 0;
	// TOTAL CUMULATIVE CASES
	unsigned totalCases;
	// NEW CASES (JUST THIS DAY)
	unsigned newCases = 0;
	// CUMULATIVE MORTALITY RATE UP TO THIS POINT
	double totalMortalityRate;
	// NEW MORTALITY RATE (JUST THIS DAY)
	double newMortalityRate = 0;
	// ADD TO CASE AND DEATH DATA
	void incData(unsigned totalDeaths, unsigned totalCases);
	// BASIC OSTREAM INCORPORATION
	friend ostream& operator<<(ostream& out, const day& today);
	// COMPARATOR FUNCTIONS FOR SORTING
	friend bool operator<(const day& d1, const day& d2);
	friend bool operator>(const day& d1, const day& d2);
	friend bool operator==(const day& d1, const day& d2);
	friend bool operator!=(const day& d1, const day& d2);
	friend bool operator<=(const day& d1, const day& d2);
	friend bool operator>=(const day& d1, const day& d2);
};

#endif