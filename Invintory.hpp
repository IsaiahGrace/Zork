#ifndef INVINTORY_HPP
#define INVINTORY_HPP
#include <string>
#include <vector>
#include "Item.hpp"

class Invintory {
public:
  Invintory() {};
  virtual ~Invintory() {};

  vector<Item> Items;

  Item& getItem(string itemName); // Retruns a refrence to the item, used as a lookup.
  void printInvintory();
};

#endif
