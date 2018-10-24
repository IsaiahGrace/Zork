#ifndef _ITEM_HPP_
#define _ITEM_HPP_
#include <string>
#include "Base.hpp"
#include "TurnOn.hpp"
#include "rapidxml.hpp"
using namespace rapidxml;

class Item : public Base {
public:
  Item(xml_node<> *node);
  virtual ~Item() { };

  string writing;
  TurnOn turnOn;
};

#endif
