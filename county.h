#ifndef COUNTY_H
#define COUNTY_H

#include "day.h"
#include "date.h"
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector>
#include <iostream>

using namespace std;

struct county {
	// DEFAULT CONSTRUCTOR TO GET THE COMPILER TO STOP YELLING AT ME
	county();
	// PARAMETERIZED CONSTRUCTOR (NO NEED FOR DEFAULT)
	county(const string &name);
	// NAME OF THE COUNTY
	string name;
	// VECTOR OF DAYS CONTAINING GROUPED DATA FOR A DATE
	vector<day> days;
	// DATE OF THE FIRST ENTRY IN DAYS
	date firstDay;
	// TOTAL NUMBER OF DEATHS IN THE COUNTY
	unsigned totalDeaths = 0;
	// TOTAL NUMBER OF CASES IN THE COUNTY
	unsigned totalCases = 0;
	// TOTAL MORTALITY RATE FOR COUNTY
	double mortalityRate = 0;
	// ADD A NEW DATE TO THE DAYS VECTOR WITH THE GIVEN CASE AND DEATH DATA
	void addDay(date &date, unsigned totalDeaths, unsigned totalCases);
	// FIND A DAY IN THE DAYS VECTOR AND RETURN A REFERENCE
	day& getDay(date &today);
	// FIND IF THE DAYS VECTOR HAS AN ENTRY FOR THE SPECIFIC DATE
	bool hasDay(date &today);
	// SORT THE LIST OF DATES BY DATE
	void sortDays();
	// TABULATE ALL THE DATA
	//    CALCULATE NEW CASES AND NEW DEATHS PER DAY
	//    CALCULATE TOTAL DEATHS AND TOTAL CASES FOR THE COUNTY
	void tabulate();
	// PRINT DATA TO A PNG FILE
	void printImage(RGBABitmapImageReference* imageReference, string& property);
	// BASIC OSTREAM INCORPORATION
	friend ostream& operator<<(ostream& out, const county& county);
	// COMPARATOR FUNCTIONS FOR SORTING
	friend bool operator<(const county& c1, const county& c2);
	friend bool operator>(const county& c1, const county& c2);
	friend bool operator==(const county& c1, const county& c2);
	friend bool operator!=(const county& c1, const county& c2);
	friend bool operator<=(const county& c1, const county& c2);
	friend bool operator>=(const county& c1, const county& c2);
};

#endif