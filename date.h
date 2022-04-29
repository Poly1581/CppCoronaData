#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

struct date {
	// DEFAULT CONSTRUCTOR
	date();
	// PARAMETERIZED CONSTRUCTOR
	date(unsigned day, unsigned month, unsigned year);
	// DAY OF THE MONTH
	unsigned day;
	// MONTH OF THE YEAR
	unsigned month;
	// YEAR
	unsigned year;
	// SET THE DAY OF THE MONTH
	void setDay(unsigned day);
	// SET THE MONTH OF THE YEAR
	void setMonth(unsigned month);
	// SET THE YEAR
	void setYear(unsigned year);
	// BASIC OSTREAM INCORPORATION
	friend ostream& operator<<(ostream& out, const date& date);
	// COMPARATOR FUNCTIONS FOR SORTING
	friend bool operator<(const date& d1, const date& d2);
	friend bool operator>(const date& d1, const date& d2);
	friend bool operator==(const date& d1, const date& d2);
	friend bool operator!=(const date& d1, const date& d2);
	friend bool operator<=(const date& d1, const date& d2);
	friend bool operator>=(const date& d1, const date& d2);
};

#endif