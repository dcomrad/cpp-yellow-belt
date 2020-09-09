#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class Date {
public:
	Date(const int new_year, const int new_month, const int new_day);
  friend bool operator<(const Date& lhs, const Date& rhs);
  friend bool operator<=(const Date& lhs, const Date& rhs);
  friend bool operator>(const Date& lhs, const Date& rhs);
  friend bool operator>=(const Date& lhs, const Date& rhs);
  friend bool operator==(const Date& lhs, const Date& rhs);
  friend bool operator!=(const Date& lhs, const Date& rhs);
	friend ostream& operator<<(ostream& os, const Date& date);
private:
	int year, month, day;
	string GetDateStr(const string& delimeter = "") const;
};

Date ParseDate(istream& is);
