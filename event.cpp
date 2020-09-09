#include "event.h"

string ParseEvent(istream& is) {
  string line;
  getline(is >> ws, line);
  return line;
}
