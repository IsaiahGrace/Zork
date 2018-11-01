#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include <string>
#include <stdio.h>
#include "Room.hpp"
#include "Item.hpp"
#include "Container.hpp"
#include "Creature.hpp"
#include "Inventory.hpp"
#include "Owner.hpp"
#include "Context.hpp"
using namespace std;
using namespace rapidxml;

class Map {
public:
  Map(FILE *fptr);
  virtual ~Map() {};
  void parseAction(string);
  // Action methods (need implimentation) REMOVE {}
  void move(string direction) {};
  void openExit() {};
  void take(string item);
  void open(string container) {};
  void read(string item) {};
  void drop(string item);
  void put(string item, string container);
  void turnOn(string item);
  void attack(string creature, string item);
  void add(string item, string owner){};
  void deleteItem(string item){};
  void update(string item, string status){};
  Room* getRoom(string);
  // Game over method throws exception
  void gameOver();
  Owner* getOwner(string);
  Item* getItem(string);
  Creature* getCreature(string);
  Context gameContext;
  Inventory playerInventory;
  vector<Room> rooms;
  vector<Item> items;
  vector<Container> containers;
  vector<Creature> creatures;
};

#endif
