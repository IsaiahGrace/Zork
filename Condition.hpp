#ifndef CONDITION_HPP
#define CONDITION_HPP
#include <string>
#include "rapidxml.hpp"
using namespace rapidxml;
using namespace std;

class Condition {
public:
  Condition(xml_node<> *node);
  virtual ~Condition() {};
  bool IsMet(void*);

  bool has;
  string object;
  string status;
  string owner;
};

#endif
