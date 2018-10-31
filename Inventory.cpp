#include <iostream>
#include "Inventory.hpp"

//I think this is empty, unless you can start with items in your inventory

Item* Inventory::getItem(string itemName) {
  for (unsigned int i = 0; i < items.size(); i++) {
    if(items[i].name == itemName) return &items[i];
  }
  return NULL; // Item not found
}

void Inventory::printInventory() {
  if(items.size()) {
    for (unsigned int i = 0; i < items.size(); i++) {
      std::cout << items[i].name << ", ";
    }
    std::cout << std::endl;
  } else {
    std::cout << "Inventory: empty" << std::endl;
  }
}
    
