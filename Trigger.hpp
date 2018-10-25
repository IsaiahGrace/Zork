#ifndef TRIGGER_HPP
#define TRIGGER_HPP
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Condition.hpp"
using namespace rapidxml;
using namespace std;

class Trigger {
public:
  Trigger(xml_node<> *node);
  virtual ~Trigger() {};
  
  string type;
  string command;
  vector<Condition> conditions;
  string print;
};

#endif
