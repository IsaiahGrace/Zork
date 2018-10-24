#include <iostream>
#include "Attack.hpp"

Attack::Attack(xml_node<> *node) {
  xml_node<> *child = node->first_node();
  
  while(child) {
    string tagName = child->name();
    std::cout << tagName << std::endl;

    if(tagName == "condition") conditions.push_back(child->value());
    else if(tagName == "print") print = child->value();
    else if(tagName == "actions") actions.push_back(child->value());

    child = child->next_sibling();
  }
}
