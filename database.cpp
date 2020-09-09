#include "database.h"

string Database::GetDayEvent(const Date& date, const string& event) const {
	stringstream ss;
	ss << date << ' ' << event;
	return ss.str();
}

void Database::Add(const Date& date, const string& event) {
	if (!events.count(date) || !events[date].count(event)) {
		auto it = events[date].insert(event);
		events_order[date].push_back(it.first);
	}
}

void Database::Print(ostream& os) const {
	for (const auto& date_events : events_order) {
		for (const auto& event : date_events.second) {
			os << GetDayEvent(date_events.first, *event) << endl;
		}
	}
}

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
	int result = 0;

	for (auto addOrderIt = events_order.begin(); addOrderIt != events_order.end(); ) {
		const Date& date = addOrderIt->first;
		vector<set<string>::iterator>& eventItList = addOrderIt->second;
		auto p = [date, predicate](const set<string>::iterator& eventIt) {
			return !predicate(date, *eventIt);
		};
		auto pIt = stable_partition(eventItList.begin(), eventItList.end(), p);
		result += eventItList.end() - pIt; //calc count of deleted items

		//delete fonded events from both maps: events and events_order
		for (auto it = pIt; it != eventItList.end(); ++it) {
			events[date].erase(*it);
		}
		eventItList.erase(pIt, eventItList.end());

		//delete map's record if set (value field) is empty
		if (addOrderIt->second.empty()) {
			events.erase(date);
			events_order.erase(addOrderIt++);
		} else {
			++addOrderIt;
		}
	}
	return result;
}

vector<string> Database::FindIf(function<bool(const Date&, const string&)> predicate) const {
	vector<string> result;
	for (const auto& date_events : events_order) {
		for (const auto& event : date_events.second) {
			if (predicate(date_events.first, *event)) {
				result.push_back(GetDayEvent(date_events.first, *event));
			}
		}
	}
	return result;
}

string Database::Last(const Date& date) const {
	auto it = events_order.upper_bound(date);
	if (!events_order.empty() && it != events_order.begin()) {
		--it;
	} else {
		throw invalid_argument("");
	}
	return GetDayEvent(it->first, *it->second.back());
}
