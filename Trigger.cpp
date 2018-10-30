#include "Trigger.hpp"
#include <iostream>

Trigger::Trigger(xml_node<> *node) {
  xml_node<> *child = node->first_node();
  //command must be initialized to emptystring to mean no command for context
  command = "";
  
  while(child) {
    string tagName = child->name();
    std::cout << "Trigger: " << tagName << std::endl;
    
    if(tagName == "type") type = child->value();
    else if(tagName == "command") command = child->value();
    else if(tagName == "condition") conditions.push_back(Condition(child));
    else if(tagName == "print") print = child->value();
		
    child = child->next_sibling();
  }
};
