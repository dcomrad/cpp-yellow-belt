#pragma once

#include "print_containers.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class TestRunner {
public:
  void RunTest(void(*func)(), const string& test_name);
  ~TestRunner();

private:
  int fail_count = 0;
};

template<typename T, typename U>
void AssertEqual(const T& t, const U& u, const string& hint) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u << " hint: " << hint;
    throw runtime_error(os.str());
  }
}
