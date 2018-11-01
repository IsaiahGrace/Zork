#ifndef ITEM_HPP
#define ITEM_HPP
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
  vector<TurnOn> turnOn;
};

#endif
