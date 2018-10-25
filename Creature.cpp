#include "Creature.hpp"
#include <iostream>

Creature::Creature(xml_node<> *node) : Base::Base(node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
    std::cout <<"Creature: " << tagName << std::endl;
    
    if(tagName == "vulnerability") vulnerability = child->value();
    else if(tagName == "attack") attack = Attack(child);

    child = child->next_sibling();
  }
}
