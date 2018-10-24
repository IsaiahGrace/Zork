#include <iostream>
#include "Invintory.hpp"

Item& Invintory::getItem(string itemName) {
  for (unsigned int i = 0; i < Items.size(); i++) {
    if(Items[i].name == itemName) return Items[i];
  }
  return NULL;
}
