#ifndef BORDER_HPP
#define BORDER_HPP
#include <string>
#include "rapidxml.hpp"
using namespace rapidxml;
using namespace std;

class Border {
public:
  Border(xml_node<> *node);
  virtual ~Border() {};
  
  string direction;
  string name;
};

#endif
