#include <iostream>
#include "Inventory.hpp"

Inventory::Inventory(): Owner::Owner(){

}

Item* Inventory::getItem(string itemName) {
  for (unsigned int i = 0; i < items.size(); i++) {
    if(items[i]->name == itemName) return items[i];
  }
  return NULL; // Item not found
}

void Inventory::printInventory() {
  if(items.size() == 1) {
    std::cout << items[0]->name << std::endl;
    return;
  }
  if(items.size() > 1) {
    for (unsigned int i = 0; i < items.size()-1; i++) {
      std::cout << items[i]->name << ", ";
    }
    std::cout << items[items.size()-1]->name << std::endl;
    return;
  }
  std::cout << "Inventory: empty" << std::endl;
  return;
}
