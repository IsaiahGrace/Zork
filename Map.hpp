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
using namespace std;
using namespace rapidxml;

class Map {
public:
  Map(FILE *fptr);
  virtual ~Map() {};
  void parseAction(string);
  // Action methods (need implimentation)
  // void move(string direction); // Takes n,s,e,w and moves the player
  // void openExit(); // checks context and ends game if approppreate (call gameOver()? Throw exception?)
  // void take(string item); // string will be the name of the item. Check context and add to inventory if approprate
  // void open(string container); // string will be the name of the container. Check context and print out the names of items in the container if appropreate
  // void read(string item); // string will be the name of an item. check context and print out the item description if appropreate
  // void drop(string item); // string will be the name of an item. Check context and move item from inventory to room if appropreate
  // void put(string item, string container); // move the item from the players inventory to the container if appropreate
  // void turnOn(string item); // string will be the name of an item in player's inventory. activate the item if appropreate
  // void attack(string creature, string item); // attack the creature with the item if item is in inventory and creature is in current room
  Room* getRoom(string);
  Owner* getOwner(string);
  Item* getItem(string);
  Inventory playerInventory;
  vector<Room> rooms;
  vector<Item> items;
  vector<Container> containers;
  vector<Creature> creatures;
};

#endif
