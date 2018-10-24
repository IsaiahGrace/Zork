#include "Border.hpp"

Border::Border(xml_node<> *node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();

    if(tagName == "direction") direction = child->value();
    else if(tagName == "name") name = child->value();
  }
}
