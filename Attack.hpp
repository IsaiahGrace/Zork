#ifndef ATTACK_HPP
#define ATTACK_HPP
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
