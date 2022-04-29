#include "date.h"
#include <iostream>

using namespace std;

date::date() {
	day = 0;
	month = 0;
	year = 0;
}

date::date(unsigned day, unsigned month, unsigned year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

void date::setDay(unsigned day) {
	this->day = day;
}

void date::setMonth(unsigned month) {
	this->month = month;
}

void date::setYear(unsigned year) {
	this->year = year;
}

ostream& operator<<(ostream& out, const date& date) {
	out << date.day << "/" << date.month << "/" << date.year;
	return out;
}

bool operator<(const date& d1, const date& d2) {
	if(d1.year < d2.year) {
		return true;
	} else if(d1.year == d2.year) {
		if(d1.month < d2.month) {
			return true;
		} else if(d1.month == d2.month) {
			if(d1.day < d2.day) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool operator>(const date& d1, const date& d2) {
	return d2 < d1;
}

bool operator==(const date& d1, const date& d2) {
	return (d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day);
}

bool operator!=(const date& d1, const date& d2) {
	return !(d1 == d2);
}

bool operator<=(const date& d1, const date& d2) {
	return (d1 < d2) || (d1 == d2);
}

bool operator>=(const date& d1, const date& d2) {
	return (d1 > d2) || (d1 == d2);
}