#include "test_runner.h"

void TestRunner::RunTest(void(*func)(), const string& test_name) {
		try {
		func();
		cerr << test_name << " OK" << endl;
	} catch (const runtime_error& e) {
		++fail_count;
		cerr << test_name << " failed: " << e.what() << endl;
	} catch (...) {
    ++fail_count;
    cerr << "Unknown exception caught" << endl;
  }
}

TestRunner::~TestRunner() {
	if (fail_count > 0) {
		cerr << fail_count << " unit tests failed. Terminate" << endl;
		exit(1);
	}
}
