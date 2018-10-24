#include "Base.hpp"
#include <iostream>

Base::Base(xml_node<> *node) {
  xml_node<> *child = node->first_node();

  while(child) {
    string tagName = child->name();
    std::cout << tagName << std::endl;
    
    if(tagName == "name") this->name = child->value();
    else if(tagName == "status") this->status = child->value();
    else if(tagName == "description") this->description = child->value();
    else if(tagName == "trigger") triggers.push_back(Trigger(child));

    child = child->next_sibling();
  }
}

