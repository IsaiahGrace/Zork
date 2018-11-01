#include "Trigger.hpp"
#include <iostream>
#include "Map.hpp"

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
    else if(tagName == "print") prints.push_back(child->value());
    else if(tagName == "action") actions.push_back(child->value());
    child = child->next_sibling();
  }

};

void Trigger::ExecuteTrigger(void* mymap){
	Map* mapptr = static_cast<Map*>(mymap);
	for(unsigned int i = 0; i < prints.size(); i++){
		std::cout << prints[i] << std::endl;
	}
	for(unsigned int j = 0; j < actions.size(); j++){
		mapptr->parseAction(actions[j]);
	}

	if(type == "single"){
		type = "used";
	}
}
