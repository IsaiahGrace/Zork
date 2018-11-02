#include "Creature.hpp"
#include <iostream>

Creature::Creature(xml_node<> *node) : Base::Base(node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
#ifndef RELEASE
    std::cout <<"Creature: " << tagName << std::endl;
#endif
    
    if(tagName == "vulnerability") vulnerability = child->value();
    else if(tagName == "attack") attack = Attack(child);

    child = child->next_sibling();
  }
}
