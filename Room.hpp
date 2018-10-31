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
#include "Owner.hpp"

class Room : public Base, public Owner {
public:
  Room(rapidxml::xml_node<> *node,void* mymap);
  virtual ~Room() {};

  bool isExit;
  //might need to be vectors of pointers

  vector<Border> borders;
  vector<Creature*> creatures;
  vector<Container*> containers;
};

#endif
