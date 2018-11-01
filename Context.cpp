#include "Context.hpp"
#include <iostream>
#include <string>

Context::Context(){
	currentRoom = NULL;
	this->inventory = NULL;
}
Context::Context(Room* startingRoom, Inventory* inventory){
  currentRoom = startingRoom;
  this->inventory = inventory;
}


void Context::parseContext(){
	//clear trigger vectors
	nonCommandTriggers.clear();
	commandTriggers.clear();

	//
	if(currentRoom != NULL){
		for(unsigned int i = 0; i < currentRoom->triggers.size(); i++){
			if(currentRoom->triggers[i].command == ""){
				nonCommandTriggers.push_back(&currentRoom->triggers[i]);
			}
			else{
				commandTriggers.push_back(&currentRoom->triggers[i]);
			}
		}
    //check containers in room
		for(unsigned int i = 0; i < currentRoom->containers.size(); i++){
			for(unsigned int j = 0; j < currentRoom->containers[i]->triggers.size(); j++){

				if(currentRoom->containers[i]->triggers[j].command == ""){
					nonCommandTriggers.push_back(&currentRoom->containers[i]->triggers[j]);
				}
				else{
					commandTriggers.push_back(&currentRoom->containers[i]->triggers[j]);
				}
			}
		}
    //check items in room
		for(unsigned int i = 0; i < currentRoom->items.size(); i++){
			for(unsigned int j = 0; j < currentRoom->items[i]->triggers.size(); j++){

				if(currentRoom->items[i]->triggers[j].command == ""){
					nonCommandTriggers.push_back(&currentRoom->items[i]->triggers[j]);
				}
				else{
					commandTriggers.push_back(&currentRoom->items[i]->triggers[j]);
				}
			}
		}
    //check creatures in room
		for(unsigned int i = 0; i < currentRoom->creatures.size(); i++){
			for(unsigned int j = 0; j < currentRoom->creatures[i]->triggers.size(); j++){

				if(currentRoom->creatures[i]->triggers[j].command == ""){
					nonCommandTriggers.push_back(&currentRoom->creatures[i]->triggers[j]);
				}
				else{
					commandTriggers.push_back(&currentRoom->creatures[i]->triggers[j]);
				}
			}
		}

	}
  //check items in inventory
	//for(unsigned int i = 0; i < commandTriggers.size(); i++){
	  //cout << "commandTrigger command:" << commandTriggers[i]->command << std::endl;
	//}

}

Trigger* Context::checkCommandTriggers(string input,void* mymap){

	for(unsigned int i = 0; i < commandTriggers.size(); i++){
		if(commandTriggers[i]->command == input){


			bool isTriggerMet = true;
			for(unsigned int j = 0; j < commandTriggers[i]->conditions.size(); j ++){
				if(commandTriggers[i]->conditions[j].IsMet(mymap)== false){
					isTriggerMet = false;
				}
			}
			if(isTriggerMet == true){
				return commandTriggers[i];
			}
		}
	}
	//no triggers are good triggers
	return NULL;


}

Trigger* Context::checkNonCommandTriggers(void* mymap){
	for(unsigned int i = 0; i < nonCommandTriggers.size(); i++){
		bool isTriggerMet = true;
		for(unsigned int j = 0; j < nonCommandTriggers[i]->conditions.size(); j ++){
			if(nonCommandTriggers[i]->conditions[j].IsMet(mymap)== false){
				isTriggerMet = false;
			}
		}
		if(isTriggerMet == true){
			return nonCommandTriggers[i];
		}
	}
	//no triggers are good triggers
	return NULL;
}

Item* Context::getItem(string itemName){

	Item* potentialItem = this->inventory->GetItem(itemName);
	if(potentialItem != NULL){
		return potentialItem;
	}

	potentialItem = this->currentRoom->GetItem(itemName);
	if(potentialItem != NULL){
		return potentialItem;
	}

	for(unsigned int i = 0; i < this->currentRoom->containers.size(); i++){
		potentialItem = this->currentRoom->containers[i]->GetItem(itemName);
		if(potentialItem != NULL){
			return potentialItem;
		}
	}

	return NULL;
}

Owner* Context::getOwner(string ownerName){

	if(ownerName == "inventory"){
		return inventory;
	}

	if(ownerName == "room"){
		return currentRoom;
	}

	for(unsigned int i = 0; i < currentRoom->containers.size(); i++){
			if(currentRoom->containers[i]->name == ownerName){
				return currentRoom->containers[i];
			}
	}

	return NULL;
}
