#ifndef REGION_H
#define REGION_H

#include "date.h"
#include "day.h"
#include "county.h"
#include "state.h"
#include <vector>
#include <iostream>


using namespace std;

struct region {
	// DEFAULT CONSTRUCTOR ONLY ONE REGION
	region(string& name);
	// NAME OF THE REGION
	string name;
	// VECTOR OF DAYS CONTAINING GROUPED DATA FOR A DATE
	vector<day> days;
	// DATE OF THE FIRST ENTRY IN DAYS
	date firstDay;
	// VECTOR OF STATES IN THE REGION
	vector<state> states;
	// TOTAL NUMBER OF DEATHS IN THE STATE
	unsigned totalDeaths = 0;
	// TOTAL NUMBER OF CASES IN THE STATE
	unsigned totalCases = 0;
	// TOTAL MORTALITY RATE IN THE STATE
	double mortalityRate = 0;
	// ADD A STATE TO THE REGION
	void addState(string &name);
	// FIND A STATE IN THE STATES VECTOR AND RETURN A REFERENCE
	state& getState(string &name);
	// CHECK TO SEE IF REGION HAS STATE ALREADY
	bool hasState(string &name);
	// SORT ALL STATES ALPHABETICALLY
	void sortStates();
	// SORT ALL DAYS WITHIN STATE
	void sortStatesDays();
	// ADD A DAY TO THE DAYS VECTOR
	void addDay(date &today, unsigned totalDeaths, unsigned totalCases);
	// FIND A DAY IN THE DAYS VECTOR AND RETURN A REFERENCE
	day& getDay(date &today);
	// CHECK TO SEE IF THE DAYS VECTOR HAS A DAY
	bool hasDay(date &today);
	// SORT THE DAYS IN THE DAYS VECTOR
	void sortDays();
	// LIFT ALL THE DAY VALUES FOR EACH STATE
	void liftDays();
	// TABULATE ALL THE DATA
	void tabulate();
	// PRINT DATA TO A PNG FILE
	void printImage(RGBABitmapImageReference* imageReference, string& property);
	// BASIC OSTREAM INCORPORATION
	friend ostream& operator<<(ostream& out, const region& region);
};

#endif