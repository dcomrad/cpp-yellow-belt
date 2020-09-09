#pragma once

#include "date.h"

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	int RemoveIf(function<bool(const Date&, const string&)> predicate);
	vector<string> FindIf(function<bool(const Date&, const string&)> predicate) const;
	string Last(const Date& date) const;
private:
	map<Date, set<string>> events;
	map<Date, vector<set<string>::iterator>> events_order;
	string GetDayEvent(const Date& date, const string& event) const;
};
