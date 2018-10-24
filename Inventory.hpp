#ifndef INVINTORY_HPP
#define INVINTORY_HPP
#include <string>
#include <vector>
#include "Item.hpp"

class Inventory {
public:
  Inventory() {};
  virtual ~Inventory() {};

  vector<Item> Items;

  Item* getItem(string itemName); // Retruns a pointer to the item, used as a lookup.
  void printInventory();
};

#endif
