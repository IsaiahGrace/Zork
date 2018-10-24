#include "Condition.hpp"

Condition::Condition(xml_node<> *node) {
	xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();

    if(tagName == "has") {
      if(child->value() == "yes") has = true;
      else if(child->value() == "no") has = false;
    }
    else if(tagName == "object") object = child->value();
    else if(tagName == "status") status = child->value();
    else if(tagName == "owner") owner = child->value();
    
    child = child->next_sibling();
  }
}
