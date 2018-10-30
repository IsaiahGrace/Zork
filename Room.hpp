#ifndef ROOM_HPP
#define ROOM_HPP
#include <vector>
#include <string>
#include "Base.hpp"
#include "Border.hpp"
#include "rapidxml.hpp"
#include "Creature.hpp"
#include "Container.hpp"
#include "Item.hpp"

class Room : public Base {
public:
  Room(rapidxml::xml_node<> *node,void* mymap);
  virtual ~Room() {};

  bool isExit;
  vector<Item> items;
  vector<Border> borders;
  vector<Creature> creatures;
  vector<Container> containers;
};

#endif
