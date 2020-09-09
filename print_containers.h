#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

//Declarations

template <typename Collection> string PrintCollection(const Collection& c, char d);
template <typename T> ostream& operator<< (ostream& os, const vector<T>& v); //vector
template <typename T> ostream& operator<< (ostream& os, queue<T> q); //queue
template <typename T> ostream& operator<< (ostream& os, const set<T>& s); //set
template <typename First, typename Second> ostream& operator<< (ostream& os, const pair<First, Second>& p); //pair
template <typename Key, typename Value> ostream& operator << (ostream& os, const map<Key, Value>& m); //map

//Definitions

template <typename Collection>
string PrintCollection(const Collection& c, char d) {
	stringstream ss;
	bool is_first = true;
	for (const auto& i : c) {
		if (!is_first) {
			ss << d;
		}
		ss << i;
		is_first = false;
	}
	return ss.str();
}

// VECTOR [1,2,3]
template <typename T>
ostream& operator<< (ostream& os, const vector<T>& v) {
	return os << '[' << PrintCollection(v, ',') << ']';
}

// QUEUE [1,2,3]
template <typename T>
ostream& operator<< (ostream& os, queue<T> q) {
	stringstream ss;
	const char d = ',';
		bool is_first = true;
		while (!q.empty()) {
			if (!is_first) {
				ss << d;
			}
			ss << q.front();
			q.pop();
			is_first = false;
		}
	return os << '[' << ss.str() << ']';
}

//SET |1,2,3|
template <typename T>
ostream& operator<< (ostream& os, const set<T>& s) {
	return os << '|' << PrintCollection(s, ',') << '|';
}

// PAIR (1,2)
template <typename First, typename Second>
ostream& operator<< (ostream& os, const pair<First, Second>& p) {
	return os << '(' << p.first << ',' << p.second << ')';
}

// MAP {1,2}
template <typename Key, typename Value>
ostream& operator << (ostream& os, const map<Key, Value>& m) {
	return os << '{' << PrintCollection(m, ',') << '}';
}
