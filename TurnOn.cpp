#include "TurnOn.hpp"
#include <iostream>

TurnOn::TurnOn(xml_node<> *node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
    std::cout << "TurnOn: " << tagName << std::endl;
    
    if(tagName == "print") printText = child->value();
    else if(tagName == "action") action.push_back(child->value());

    child = child->next_sibling();
  }
}
