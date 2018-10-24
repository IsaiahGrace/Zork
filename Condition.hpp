#ifndef _CONDITION_HPP_
#define _CONDITION_HPP_
#include <string>
#include "rapidxml.hpp"
using namespace rapidxml;
using namespace std;

class Condition {
public:
  Condition(xml_node<> *node);
  virtual ~Condition() {};

  bool has;
  string object;
  string status;
  string owner;
};

#endif
