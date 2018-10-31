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
  void ExecuteTrigger(void*);
  
  string type;
  string command;
  vector<Condition> conditions;
  vector<string> prints;
  vector<string> actions;
};

#endif
