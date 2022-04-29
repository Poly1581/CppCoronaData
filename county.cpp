#include "date.h"
#include "day.h"
#include "county.h"
#include <iostream>
#include <algorithm>

using namespace std;

county::county() {

}

county::county(const string &name) {
	this->name = name;
}

void county::addDay(date &today, unsigned totalDeaths, unsigned totalCases) {
	if(days.size() != 0) {
		if(!hasDay(today)) {
			day newDay(today, totalDeaths, totalCases);
			days.push_back(newDay);
		}
	} else {
		day newDay(today, totalDeaths, totalCases);
		days.push_back(newDay);
		firstDay = today;
	}
}

day& county::getDay(date &today){
	for(unsigned i = 0; i < days.size(); i++) {
		if(days.at(i).today == today) {
			return days.at(i);
		}
	}
	return *(new day(date(),0,0));
}

bool county::hasDay(date &today) {
	for(unsigned i = 0; i < days.size(); i++) {
		if(days.at(i).today == today) {
			return true;
		}
	}
	return false;
}

void county::sortDays() {
	sort(days.begin(),days.end());
}

void county::tabulate() {
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

void county::printImage(RGBABitmapImageReference* imageReference, string& property) {
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

ostream& operator<<(ostream& out, const county& county) {
	out << "COUNTY:\t" << county.name << endl;
	for(unsigned i = 0; i < county.days.size(); i++) {
		out << " " << county.days.at(i) << endl;
	}
	return out;
}

bool operator<(const county& c1, const county& c2) {
	return c1.name < c2.name;
}

bool operator>(const county& c1, const county& c2) {
	return c1.name > c2.name;
}

bool operator==(const county& c1, const county& c2) {
	return c1.name == c2.name;
}

bool operator!=(const county& c1, const county& c2) {
	return c1.name != c2.name;
}

bool operator<=(const county& c1, const county& c2) {
	return c1.name <= c2.name;
}

bool operator>=(const county& c1, const county& c2) {
	return c1.name >= c2.name;
}