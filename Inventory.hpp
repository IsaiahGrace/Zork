#ifndef INVINTORY_HPP
#define INVINTORY_HPP
#include <string>
#include <vector>
#include "Item.hpp"
#include "Owner.hpp"

class Inventory : public Owner{
public:
  Inventory();
  virtual ~Inventory() {};
  //Might need to be a vector of pointers
  //vector<Item> items;

  Item* getItem(string itemName); // Retruns a pointer to the item, used as a lookup.
  void printInventory();
  
};

#endif
