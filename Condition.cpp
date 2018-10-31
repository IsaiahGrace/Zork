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

bool Condition::IsMet(void* mymap){
	Map* mapptr = static_cast<Map*>(mymap);


	if(status != ""){
		return this->StatusMet(mymap);
	}

	if(owner == "inventory"){
		if(has == true){
			//true if object exists, false if does not exist.
			if(mapptr->playerInventory.getItem(object) == NULL){
				return false;
			}
			return true;
		}
		else{
			//true if object does not exist, false if it does
			if(mapptr->playerInventory.getItem(object) == NULL){
				return true;
			}
			return false;
		}
	}

	//we only get here if owner is not inventory
	//must check owner objects

	Owner* ownerMatch=mapptr->getOwner(owner);
	if(ownerMatch==NULL){
		//this shouldn't happen
		return false;
	}

	if(has == true){
		//if item is found, then owner has object
		if(ownerMatch->FindItem(object) == true){
			return true;
		}
		return false;
	}
	else{
		//if item is not found, owner does not have object
		if(ownerMatch->FindItem(object) == false){
			return true;
		}
		return false;
	}

}

//TODO: this function
//get item from map
//check if it has status
bool Condition::StatusMet(void* mymap){
	Map* mapptr = static_cast<Map*>(mymap);

	return false;
}
