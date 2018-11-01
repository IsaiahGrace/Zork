#ifndef TURNON_HPP
#define TURNON_HPP

#include <string>
#include <vector>
#include "rapidxml.hpp"
using namespace std;
using namespace rapidxml;

class TurnOn {
public:
  TurnOn() {};
  TurnOn(xml_node<> *node);
  virtual ~TurnOn() {};

  string printText;
  vector<string> action;
};

#endif
