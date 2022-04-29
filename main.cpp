#include "date.h"
#include "day.h"
#include "county.h"
#include "state.h"
#include "region.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


// DATA FORMAT:
//    date, county, state, fips, cases, deaths

bool readData(istream &in, unsigned& year, unsigned& day, unsigned& month, string& countyName, string& stateName, unsigned& cases, unsigned& deahts);

void printImage(RGBABitmapImageReference* imageReference, string& property);

int main(int argc, char **argv) {
	//Download the most recent data
	string command = "curl -O https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-counties.csv";
	cout << "DOWNLOADING MOST RECENT DATA" << endl;
	system(command.c_str());
	cout << "FINISHED DOWNLOADING DATA" << endl;


	// File stream stuff
	string filename = argc>1?argv[1]:"us-counties.csv";
	ifstream input;
	input.open(filename);
	if(!input.is_open()) {
		cout << "ERROR OPENING FILE:\t" << filename << endl;
		return 1;
	}

	// Variable stuff
	unsigned year;
	unsigned day;
	unsigned month;
	string county_name;
	string state_name;
	unsigned cases;
	unsigned deaths;

	// Make region
	string regionName = "United States";
	region US(regionName);

	// Read csv input
	getline(input,county_name);
	while(readData(input, year, day, month, county_name, state_name, cases, deaths)) {
		date today(day, month, year);
		US.addState(state_name);
		US.getState(state_name).addCounty(county_name);
		US.getState(state_name).getCounty(county_name).addDay(today, deaths, cases);
	}

	// Make sure the last line data gets added
	date today(day, month, year);
	US.addState(state_name);
	US.getState(state_name).addCounty(county_name);
	US.getState(state_name).getCounty(county_name).addDay(today, deaths, cases);
	US.tabulate();

	// Loop to access data
	string property;
	string level;
	state s;
	county c;
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
	while(true) {
		start:
		cout << US << endl;
		cout << "Enter State name:\n\t(enter here if you want to analyze US data trends)\n\t(Enter EXIT to quit program)" << endl;
		getline(cin,state_name);
		if(state_name == "EXIT") {
			return 1;
		}
		if(state_name == "here") {
			level = "region";
			goto getproperty;
		}
		if(!US.hasState(state_name)) {
			cout << "INVALID STATE SELECTION" << endl;
			goto start;
		}
		s = US.getState(state_name);
		cout << s << endl;
		cout << "Enter County name:\n\t(enter here if you want to analyze " << state_name << " data trends)" << endl;
		getline(cin,county_name);
		if(county_name == "here") {
			level = "state";
			goto getproperty;
		}
		if(!s.hasCounty(county_name)) {
			cout << "INVALID COUNTY SELECTION" << endl;
			goto start;
		}
		level = "county";
		c = s.getCounty(county_name);
		getproperty:
		cout << "Enter property to be analyzed:\n\tnewDeaths\tnewCases\ttotalDeaths\ttotalCases\tALL" << endl;
		getline(cin,property);
		if(property != "newCases" && property != "newDeaths" && property != "totalCases" && property != "totalDeaths" && property != "ALL") {
			cout << "INVALID PROPERTY SELECTION" << endl;
			goto start;
		}
		if(level == "region") {
			US.printImage(imageReference,property);
		} else if(level == "state") {
			s.printImage(imageReference,property);
		} else if(level == "county") {
			c.printImage(imageReference,property);
		}
	}
}



bool readData(istream& in, unsigned& year, unsigned& day, unsigned& month, string& countyName, string& stateName, unsigned& cases, unsigned& deaths) {
	string inputString;
	string line;
	getline(in,line);
	stringstream currLine(line);
	getline(currLine,inputString,',');
	stringstream currDate(inputString);
	getline(currDate,inputString,'-');
	year = (unsigned)stoi(inputString);
	getline(currDate,inputString,'-');
	month = (unsigned)stoi(inputString);
	getline(currDate,inputString,'-');
	day = (unsigned)stoi(inputString);
	getline(currLine,inputString,',');
	countyName = inputString;
	getline(currLine,inputString,',');
	stateName = inputString;
	getline(currLine,inputString,',');
	getline(currLine,inputString,',');
	cases = (unsigned)stoi(inputString);
	getline(currLine,inputString,',');
	deaths = stateName=="Puerto Rico"?0:(unsigned)stoi(inputString);
	return !in.eof();
}

// COMPILATION COMMAND
//    g++ -o source main.o date.o day.o county.o state.o region.o pbPlots.o supportLib.o