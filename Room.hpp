#ifndef ROOM_HPP
#define ROOM_HPP
#include <vector>
#include <string>
#include "Base.hpp"
#include "Border.hpp"
#include "rapidxml.hpp"
using namespace rapidxml;

class Room : public Base {
public:
  Room(xml_node<> *node);
  virtual ~Room() {};

  bool isExit;
  vector<string> items;
  vector<Border> borders;
};

#endif
