#include "Item.hpp"
#include <iostream>

Item::Item(xml_node<> *node) : Base::Base(node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
    std::cout << tagName << std::endl;
    
    if(tagName == "writing") writing = child->value();
    else if(tagName == "turnon") turnOn = TurnOn(child);

    child = child->next_sibling();
  }
}
