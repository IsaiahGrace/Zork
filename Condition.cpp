#include "Condition.hpp"
#include "Map.hpp"
#include <iostream>

Condition::Condition(xml_node<> *node) {
	xml_node<> *child = node->first_node();
	status = "";
  while(child) {
    string tagName = child->name();
    std::cout <<"Condition: "<< tagName << std::endl;
    
    if(tagName == "has") {
      if(string(child->value()) == "yes") has = true;
      else if(string(child->value()) == "no") has = false;
    }
    else if(tagName == "object") object = child->value();
    else if(tagName == "status") status = child->value();
    else if(tagName == "owner") owner = child->value();
    
    child = child->next_sibling();
  }
}

//bool Condition::IsMet(void* mymap){
//	Map* mapptr = static_cast<Map*>(mymap);


//}
