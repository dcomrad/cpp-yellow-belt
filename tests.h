#pragma once

#include "test_runner.h"
#include "event.h"
#include "condition_parser.h"
#include "database.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

void TestAll();
void TestDate();
void TestParseEvent();
void TestParseCondition();
void TestDB();
