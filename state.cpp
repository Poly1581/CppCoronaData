#include "date.h"
#include "day.h"
#include "county.h"
#include "state.h"
#include <iostream>
#include <algorithm>

using namespace std;

state::state() {

}

state::state(string &name) {
	this->name = name;
}

void state::addCounty(string &name) {
	if(!hasCounty(name)) {
		county newCounty(name);
		counties.push_back(newCounty);
	}
}

county& state::getCounty(string &name) {
	for(unsigned i = 0; i < counties.size(); i++) {
		if(counties.at(i).name == name) {
			return counties.at(i);
		}
	}
	return *(new county());
}

bool state::hasCounty(string &name) {
	for(unsigned i = 0; i < counties.size(); i++) {
		if(counties.at(i).name == name) {
			return true;
		}
	}
	return false;
}

void state::sortCounties() {
	sort(counties.begin(), counties.end());
}

void state::sortCountiesDays() {
	for(unsigned i = 0; i < counties.size(); i++) {
		counties.at(i).sortDays();
	}
}

void state::addDay(date &today, unsigned totalDeaths, unsigned totalCases) {
	if(days.size()!=0) {
		if(!hasDay(today)) {
			day newDay(today, totalDeaths, totalCases);
			days.push_back(newDay);
			if(today < firstDay) {
				firstDay = today;
			}
		} else {
			cout << "Already have day " << today << " in state " << name << endl;
		}
	} else {
		day newDay(today, totalDeaths, totalCases);
		days.push_back(newDay);
		firstDay = today;
	}
}

day& state::getDay(date &today) {
	for(unsigned i = 0; i < days.size(); i++) {
		if(days.at(i).today == today) {
			return days.at(i);
		}
	}
	cout << "No day " << today << " in state " << name << endl;
	return *(new day(date(),0,0));
}

bool state::hasDay(date &today) {
	for(unsigned i = 0; i < days.size(); i++) {
		if(days.at(i).today == today) {
			return true;
		}
	}
	return false;
}

void state::sortDays() {
	sort(days.begin(), days.end());
}

void state::liftDays() {
	sortCounties();
	sortCountiesDays();
	for(unsigned c = 0; c < counties.size(); c++) {
		for(unsigned d = 0; d < counties.at(c).days.size(); d++) {
			day currDay = counties.at(c).days.at(d);
			if(!hasDay(currDay.today)) {
				days.push_back(currDay);
			} else {
				getDay(currDay.today).incData(currDay.totalDeaths,currDay.totalCases);
			}
		}
	}
}

void state::tabulate() {
	for(unsigned c = 0; c < counties.size(); c++) {
		counties.at(c).tabulate();
	}
	liftDays();
	sortDays();
	totalDeaths = days.at(days.size()-1).totalDeaths;
	totalCases = days.at(days.size()-1).totalDeaths;
	mortalityRate = totalDeaths/(double)totalCases;
	for(unsigned i = 1; i < days.size(); i++) {
		if(days.at(i).totalDeaths > days.at(i-1).totalDeaths) {
			days.at(i).newDeaths = days.at(i).totalDeaths - days.at(i-1).totalDeaths;
		}
		if(days.at(i).totalCases > days.at(i-1).totalCases) {
			days.at(i).newCases = days.at(i).totalCases - days.at(i-1).totalCases;
		}
	}
}

void state::printImage(RGBABitmapImageReference* imageReference, string& property) {
	vector<double> xs;
	vector<double> ys;
	if(property == "newCases" || property == "ALL") {
		for(unsigned d = 0; d < days.size(); d++) {
			xs.push_back((double)d);
			ys.push_back((double)days.at(d).newCases);
		}
		DrawScatterPlot(imageReference,1920,1080,&xs,&ys);
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		string filename = "./imgs/"+name+"newCases.png";
		WriteToFile(pngdata,filename);
	}
	if(property == "newDeaths" || property == "ALL") {
		for(unsigned d = 0; d < days.size(); d++) {
			xs.push_back((double)d);
			ys.push_back((double)days.at(d).newDeaths);
		}
		DrawScatterPlot(imageReference,1920,1080,&xs,&ys);
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		string filename = "./imgs/"+name+"newDeaths.png";
		WriteToFile(pngdata,filename);
	}
	if(property == "totalCases" || property == "ALL") {
		for(unsigned d = 0; d < days.size(); d++) {
			xs.push_back((double)d);
			ys.push_back((double)days.at(d).totalCases);
		}
		DrawScatterPlot(imageReference,1920,1080,&xs,&ys);
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		string filename = "./imgs/"+name+"totalCases.png";
		WriteToFile(pngdata,filename);
	}
	if(property == "totalDeaths" || property == "ALL") {
		for(unsigned d = 0; d < days.size(); d++) {
			xs.push_back((double)d);
			ys.push_back((double)days.at(d).totalDeaths);
		}
		DrawScatterPlot(imageReference,1920,1080,&xs,&ys);
		vector<double> *pngdata = ConvertToPNG(imageReference->image);
		string filename = "./imgs/"+name+"totalDeaths.png";
		WriteToFile(pngdata,filename);
	}
}

ostream& operator<<(ostream& out, const state& state) {
	out << "STATE:\t"<< state.name << endl;
	for(unsigned i = 0; i < state.counties.size(); i++) {
		out <<  "\t" << state.counties.at(i).name << endl;
	}
	return out;
}

bool operator<(const state& s1, const state& s2) {
	return s1.name < s2.name;
}

bool operator>(const state& s1, const state& s2) {
	return s1.name > s2.name;
}

bool operator==(const state& s1, const state& s2) {
	return s1.name == s2.name;
}

bool operator!=(const state& s1, const state& s2) {
	return s1.name != s2.name;
}

bool operator<=(const state& s1, const state& s2) {
	return s1.name <= s2.name;
}

bool operator>=(const state& s1, const state& s2) {
	return s1.name >= s2.name;
}