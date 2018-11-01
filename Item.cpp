#include "Item.hpp"
#include <iostream>

Item::Item(xml_node<> *node) : Base::Base(node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
    std::cout <<"Item: " << tagName << std::endl;
    
    if(tagName == "writing") writing = child->value();
    else if(tagName == "turnon") turnOn.push_back(TurnOn(child));

    child = child->next_sibling();
  }
}
