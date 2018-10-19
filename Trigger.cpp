#include "Trigger.hpp"

Trigger::Trigger(xml_node<> *node) {
  xml_node<> *child = node->first_node();
  
  while(child) {
    string tagName = child->name();

    if(tagName == "type") type = child->value();
    else if(tagName == "command") command = child->value();
    else if(tagName == "condition") conditions.push_back(Condition(child));
    else if(tagName == "print") print = child->value();
		
    child = child->next_sibling();
  }
};
