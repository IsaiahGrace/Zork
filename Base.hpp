#ifndef BASE_HPP
#define BASE_HPP
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Trigger.hpp"
using namespace std;
using namespace rapidxml;

class Trigger;

class Base {
public:
  Base() {};
  Base(xml_node<> *node);
  virtual ~Base() {};

  string name;
  string status;
  string description;
  vector<Trigger> triggers;
};

#endif
