#include "date.h"

Date::Date(const int new_year, const int new_month, const int new_day) {
		if (new_year < 0 || new_year > 9999) {
			throw out_of_range("Year is invalid: " + to_string(new_year));
		}
		if (new_month < 1 || new_month > 12) {
			throw out_of_range("Month is invalid: " + to_string(new_month));
		}
		if (new_day < 1 || new_day > 31) {
			throw out_of_range("Day is invalid: " + to_string(new_day));
		}

		year = new_year;
		month = new_month;
		day = new_day;
	}

string Date::GetDateStr(const string& delimeter) const {
	stringstream ss;
	ss << setw(4) << setfill('0') << year << delimeter
		 << setw(2) << setfill('0') << month << delimeter
		 << setw(2) << setfill('0') << day;
	return ss.str();
}

bool operator<(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) <= tie(rhs.year, rhs.month, rhs.day);
}

bool operator>(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) > tie(rhs.year, rhs.month, rhs.day);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) >= tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) != tie(rhs.year, rhs.month, rhs.day);
}

ostream& operator<<(ostream& os, const Date& date) {
	return os << date.GetDateStr("-");
}

Date ParseDate(istream& is) {
	bool is_ok = true;

	int year;
	is_ok = is_ok && (is >> year);
	is_ok = is_ok && (is.peek() == '-');
	is.ignore();

	int month;
	is_ok = is_ok && (is >> month);
	is_ok = is_ok && (is.peek() == '-');
	is.ignore();

	int day;
	is_ok = is_ok && (is >> day);

	if (!is_ok) {
		throw runtime_error("Wrong date format");
	}

	return {year, month, day};
}
