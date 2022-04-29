#include "day.h"
#include "date.h"
#include <iostream>

using namespace std;

day::day(const date &today, unsigned totalDeaths, unsigned totalCases) {
	this->today = today;
	this->totalDeaths = totalDeaths;
	this->totalCases = totalCases;
	this->totalMortalityRate = totalDeaths/(double)totalCases;
}

void day::incData(unsigned totalDeaths, unsigned totalCases) {
	this->totalDeaths+= totalDeaths;
	this->totalCases+= totalCases;
}


ostream& operator<<(ostream& out, const day& day) {
	out << day.today << " : " << day.newDeaths << " new deaths, " << day.totalDeaths << " total deaths, " << day.newCases << " new cases, and " << day.totalCases << " total cases";
	return out;
}

bool operator<(const day& d1, const day& d2) {
 	return d1.today < d2.today;
}

bool operator>(const day& d1, const day& d2) {
	return d1.today > d2.today;
}

bool operator==(const day& d1, const day& d2) {
	return d1.today == d2.today;
}

bool operator!=(const day& d1, const day& d2) {
	return d1.today != d2.today;
}

bool operator<=(const day& d1, const day& d2) {
	return d1.today <= d2.today;
}

bool operator>=(const day& d1, const day& d2) {
	return d1.today >= d2.today;
}