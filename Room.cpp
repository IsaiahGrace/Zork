#include "Room.hpp"
#include "Map.hpp"
#include "Owner.hpp"
#include <iostream>


Room::Room(xml_node<char> *node,void* mymap) : Base::Base(node),Owner::Owner(node,mymap) {
  Map* mapptr = static_cast<Map*>(mymap);
  xml_node<> *child = node->first_node();

  isExit = false;

  while(child) {
    string tagName = child->name();
    std::cout << "Room: "<<  tagName << std::endl;

    /*
     * this block here goes through all initialized items/containers/creatures
     * and finds if their name was defined
     * if it is, it adds them to the room
     */

    if(tagName == "creature"){
    	for(unsigned int i = 0; i < mapptr->creatures.size();i++){
    		if(mapptr->creatures[i].name == child->value()){
    			std::cout << "Creature:" << mapptr->creatures[i].name << "added to room"<< std::endl;
    			creatures.push_back(&mapptr->creatures[i]);
    		}
    	}
    }
    else if(tagName == "container"){
    	for(unsigned int i = 0; i < mapptr->containers.size();i++){
    		if(mapptr->containers[i].name == child->value()){
    			std::cout << "Container:" << mapptr->containers[i].name << "added to room"<< std::endl;
    			containers.push_back(&mapptr->containers[i]);
    		}
    	}
    }

    else if(tagName == "border") borders.push_back(Border(child));
    else if(tagName == "type") isExit = true; // Only rooms with exits have the <type> tagName

    child = child->next_sibling();
  }
}

Creature* Room::getCreature(string creatureName){
	  for (unsigned int i = 0; i < creatures.size(); i++) {
		  if(creatures[i]->name == creatureName) return creatures[i];
	  }
	  	  return NULL; // Item not parseAction
}

Item* Room::getItem(string itemName) {
  for (unsigned int i = 0; i < items.size(); i++) {
    if(items[i]->name == itemName){
    	return items[i];
    }
  }
  return NULL; // Item not found
}
