#ifndef _CREATURE_HPP_
#define _CREATURE_HPP_
#include <vector>
#include <string>
#include "rapidxml.hpp"
#include "Base.hpp"
#include "Attack.hpp"
using namespace rapidxml;

class Creature : public Base {
public:
  Creature(xml_node<> *node);
  virtual ~Creature() {};

  string vulnerability;
  Attack attack;
};

#endif
