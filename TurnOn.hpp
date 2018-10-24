#ifndef _TURNON_HPP_
#define _TURNON_HPP_

#include <string>
#include "rapidxml.hpp"
using namespace std;
using namespace rapidxml;

class TurnOn {
public:
  TurnOn() {};
  TurnOn(xml_node<> *node);
  virtual ~TurnOn() {};

  string printText;
  string action;
};

#endif
