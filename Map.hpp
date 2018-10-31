#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include <string>
#include <stdio.h>
#include "Room.hpp"
#include "Item.hpp"
#include "Container.hpp"
#include "Creature.hpp"
#include "inventory.hpp"
using namespace std;
using namespace rapidxml;

class Map {
public:
  Map(FILE *fptr);
  virtual ~Map() {};
  Room* getRoom(string);
  Inventory playerInventory;
  vector<Room> rooms;
  vector<Item> items;
  vector<Container> containers;
  vector<Creature> creatures;
};

#endif
