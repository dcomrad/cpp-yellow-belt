#include "tests.h"

void TestAll() {
	TestRunner tr;
  tr.RunTest(TestDate, "TestDate");
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  tr.RunTest(TestDB, "TestDB");
}

void TestDate() {
	//test ParseDate
	{
		stringstream ss("2017-01-01");
		Date date(ParseDate(ss));
		AssertEqual(date, Date(2017,1,1), "ParseDate test 1");
	}
	{
		stringstream ss("0001-01-01");
		Date date(ParseDate(ss));
		AssertEqual(date, Date(1,1,1), "ParseDate test 2");
	}

	//test Date comparison
	{
		Date date1(2017,1,1);
		Date date2(2017,1,1);
		Date date3(2015,1,1);
		Date date4(2018,1,1);
		AssertEqual(date1 == date2, true, "Date comparison test 1");
		AssertEqual(date1 != date3, true, "Date comparison test 4");
		AssertEqual(date1 >= date2, true, "Date comparison test 2");
		AssertEqual(date1 <= date2, true, "Date comparison test 3");
		AssertEqual(date3 < date1, true, "Date comparison test 5");
		AssertEqual(date4 > date1, true, "Date comparison test 6");
	}
	{
		Date date1(2017, 1, 1);
		Date date2(2017, 7, 1);
		Date date3(2017, 6, 30);
		AssertEqual(date3 >= date1, true, "Date comparison test 7");
		AssertEqual(date3 < date2, true, "Date comparison test 8");
	}
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestParseCondition() {
  {
    istringstream is("date != 2017-11-18");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2017, 1, 1}, ""), true, "Parse condition 1");
    AssertEqual(root->Evaluate({2017, 11, 18}, ""), false, "Parse condition 2");
  }
  {
    istringstream is(R"(event == "sport event")");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2017, 1, 1}, "sport event"), true, "Parse condition 3");
    AssertEqual(root->Evaluate({2017, 1, 1}, "holiday"), false, "Parse condition 4");
  }
  {
    istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2017, 1, 1}, ""), true, "Parse condition 5");
    AssertEqual(root->Evaluate({2017, 3, 1}, ""), true, "Parse condition 6");
    AssertEqual(root->Evaluate({2017, 6, 30}, ""), true, "Parse condition 7");
    AssertEqual(root->Evaluate({2017, 7, 1}, ""), false, "Parse condition 8");
    AssertEqual(root->Evaluate({2016, 12, 31}, ""), false, "Parse condition 9");
  }
  {
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2017, 1, 1}, "holiday"), true, "Parse condition 10");
    AssertEqual(root->Evaluate({2017, 1, 1}, "sport event"), false, "Parse condition 11");
    AssertEqual(root->Evaluate({2017, 1, 1}, "Wednesday"), false, "Parse condition 12");
  }
  {
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2017, 11, 18}, "holiday"), false, "Parse condition 13");
    AssertEqual(root->Evaluate({2017, 11, 18}, "work day"), false, "Parse condition 14");
    AssertEqual(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), true, "Parse condition 15");
  }
  {
    istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2017, 1, 1}, "holiday"), true, "Parse condition 16");
    AssertEqual(root->Evaluate({2017, 1, 2}, "holiday"), false, "Parse condition 17");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2016, 1, 1}, "holiday"), false, "Parse condition 18");
    AssertEqual(root->Evaluate({2017, 1, 2}, "holiday"), true, "Parse condition 19");
    AssertEqual(root->Evaluate({2017, 1, 2}, "workday"), true, "Parse condition 20");
    AssertEqual(root->Evaluate({2018, 1, 2}, "workday"), false, "Parse condition 21");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2016, 1, 1}, "event"), true, "Parse condition 22");
    AssertEqual(root->Evaluate({2017, 1, 2}, "holiday"), true, "Parse condition 23");
    AssertEqual(root->Evaluate({2017, 1, 2}, "workday"), true, "Parse condition 24");
    AssertEqual(root->Evaluate({2018, 1, 2}, "workday"), false, "Parse condition 25");
  }
  {
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({2017, 1, 1}, "holiday"), true, "Parse condition 26");
    AssertEqual(root->Evaluate({2017, 1, 2}, "holiday"), false, "Parse condition 27");
  }
  {
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    AssertEqual(root->Evaluate({1, 1, 1}, "2017-01-01"), true, "Parse condition 28");
    AssertEqual(root->Evaluate({2016, 1, 1}, "event"), false, "Parse condition 29");
    AssertEqual(root->Evaluate({2016, 1, 2}, "event"), true, "Parse condition 30");
  }
}

void TestDB() {
	istringstream empty_is("");
	auto empty_condition = ParseCondition(empty_is);
	auto empty_predicate = [empty_condition](const Date& date, const string& event) {
		return empty_condition->Evaluate(date, event);
	};

  // Add
  {
    Database db;
    Date d(2019, 1, 1);
    db.Add(d, "e1");
    db.Add(d, "e1");
    istringstream is("date == 2019-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.FindIf(predicate).size(), 1u, "Db Add Duplicates 1");
  }
}
