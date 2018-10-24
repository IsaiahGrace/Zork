#include "TurnOn.hpp"

TurnOn::TurnOn(xml_node<> *node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();

    if(tagName == "print") printText = child->value();
    else if(tagName == "action") action = child->value();

    child = child->next_sibling();
  }
}
