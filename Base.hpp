#ifndef _BASE_HPP_
#define _BASE_HPP_
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

  //static Base *search(vector<Base> *bases, string name);

  string name;
  string status;
  string description;
  vector<Trigger> triggers;
};

#endif
