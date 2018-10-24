#include "Border.hpp"
#include <iostream>

Border::Border(xml_node<> *node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
    std::cout << tagName << std::endl;
    
    if(tagName == "direction") direction = child->value();
    else if(tagName == "name") name = child->value();

    child = child->next_sibling();
  }
}
