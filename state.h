#ifndef STATE_H
#define STATE_H

#include "date.h"
#include "day.h"
#include "county.h"
#include <vector>
#include <iostream>

using namespace std;

struct state {
	// DEFAULT CONSTRUCTOR TO GET THE COMPILER TO STOP YELLING AT ME
	state();
	// PARAMETERIZED CONSTRUCTOR (NO NEED FOR DEFAULT)
	state(string &name);
	// NAME OF THE STATE (OR REGION)
	string name;
	// VECTOR OF DAYS CONTAINING GROUPED DATA FOR A DATE
	vector<day> days;
	// DATE OF THE FIRST ENTRY IN DAYS
	date firstDay;
	// VECTOR OF COUNTIES IN THE STATE
	vector<county> counties;
	// TOTAL NUMBER OF DEATHS IN THE STATE
	unsigned totalDeaths = 0;
	// TOTAL NUMBER OF CASES IN THE STATE
	unsigned totalCases = 0;
	// TOTAL MORTALITY RATE IN THE STATE
	double mortalityRate = 0;
	// ADD A COUNTY IN THE STATE
	void addCounty(string &name);
	// FIND A COUNTY IN THE COUNTIES VECTOR AND RETURN A REFERENCE
	county& getCounty(string &name);
	// CHECK TO SEE IF STATE HAS COUNTRY ALREADY
	bool hasCounty(string &name);
	// SORT ALL COUNITES ALPHABETICALLY
	void sortCounties();
	// SORT ALL DAYS WITHIN COUNTY
	void sortCountiesDays();
	// ADD A DAY TO THE DAYS VECTOR
	void addDay(date &today, unsigned totalDeaths, unsigned totalCases);
	// FIND A DAY IN THE DAYS VECTOR AND RETURN A REFERENCE
	day& getDay(date &today);
	// CHECK TO SEE IF THE DAYS VECTOR HAS A DAY
	bool hasDay(date &today);
	// SORT THE DAYS IN THE DAYS VECTOR
	void sortDays();
	// LIFT ALL THE DAY VALUES FOR EACH COUNTY
	void liftDays();
	// TABULATE ALL THE DATA
	void tabulate();
	// PRINT DATA TO A PNG FILE
	void printImage(RGBABitmapImageReference* imageReference, string& property);
	// BASIC OSTREAM INCORPORATION
	friend ostream& operator<<(ostream& out, const state& state);
	// COMPARATOR FUNCTIONS FOR SORTING
	friend bool operator<(const state& c1, const state& c2);
	friend bool operator>(const state& c1, const state& c2);
	friend bool operator==(const state& c1, const state& c2);
	friend bool operator!=(const state& c1, const state& c2);
	friend bool operator<=(const state& c1, const state& c2);
	friend bool operator>=(const state& c1, const state& c2);
};

#endif