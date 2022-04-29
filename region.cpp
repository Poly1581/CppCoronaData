#include "date.h"
#include "day.h"
#include "county.h"
#include "state.h"
#include "region.h"
#include <iostream>
#include <algorithm>

using namespace std;

region::region(string& name) {
	this->name = name;
}

void region::addState(string &name) {
	if(!hasState(name)) {
		state newState(name);
		states.push_back(newState);
	}
}

state& region::getState(string &name) {
	for(unsigned i = 0; i < states.size(); i++) {
		if(states.at(i).name == name) {
			return states.at(i);
		}
	}
	return *(new state());
}

bool region::hasState(string &name) {
	for(unsigned i = 0; i < states.size(); i++) {
		if(states.at(i).name == name) {
			return true;
		}
	}
	return false;
}

void region::sortStates() {
	sort(states.begin(), states.end());
}

void region::sortStatesDays() {
	for(unsigned i = 0; i < states.size(); i++) {
		states.at(i).sortDays();
	}
}

void region::addDay(date &today, unsigned totalDeaths, unsigned totalCases) {
	if(days.size()!=0) {
		if(!hasDay(today)) {
			day newDay(today, totalDeaths, totalCases);
			days.push_back(newDay);
			if(today < firstDay) {
				firstDay = today;
			}
		} else {
			cout << "Already have day " << today << " in this region." << endl;
		}
	} else {
		day newDay(today, totalDeaths, totalCases);
		days.push_back(newDay);
		firstDay = today;
	}
}

day& region::getDay(date &today) {
	for(unsigned i = 0; i < days.size(); i++) {
		if(days.at(i).today == today) {
			return days.at(i);
		}
	}
	cout << "No day " << today << " in this region." << endl;
	return *(new day(date(),0,0));
}

bool region::hasDay(date &today) {
	for(unsigned i = 0; i < days.size(); i++) {
		if(days.at(i).today == today) {
			return true;
		}
	}
	return false;
}

void region::sortDays() {
	sort(days.begin(), days.end());
}

void region::liftDays() {
	sortStates();
	sortStatesDays();
	for(unsigned s = 0; s < states.size(); s++) {
		for(unsigned d = 0; d < states.at(s).days.size(); d++) {
			day currDay = states.at(s).days.at(d);
			if(!hasDay(currDay.today)) {
				days.push_back(currDay);
			} else {
				getDay(currDay.today).incData(currDay.totalDeaths,currDay.totalCases);
			}
		}
	}
}

void region::tabulate() {
	for(unsigned s = 0; s < states.size(); s++) {
		states.at(s).tabulate();
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

void region::printImage(RGBABitmapImageReference* imageReference, string& property) {
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

ostream& operator<<(ostream& out, const region& region) {
	out << "REGION:\t" << region.name << endl;
	for(unsigned i = 0; i < region.states.size(); i++) {
		out << "\t" << region.states.at(i).name << endl;
	}
	return out;
}