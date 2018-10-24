#ifndef _ATTACK_HPP_
#define _ATTACK_HPP_
#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Condition.hpp"
using namespace rapidxml;

class Attack {
public:
  Attack() {};
  Attack(xml_node<> *node);
  virtual ~Attack() {};

  vector<string> conditions;
  string print;
  vector<string> actions;
};

#endif
