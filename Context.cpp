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

	//check room triggers
	if(currentRoom != NULL){
		for(unsigned int i = 0; i < currentRoom->triggers.size(); i++){
			if(currentRoom->triggers[i].type != "used"){
				if(currentRoom->triggers[i].command == ""){
					nonCommandTriggers.push_back(&currentRoom->triggers[i]);
				}
				else{
					commandTriggers.push_back(&currentRoom->triggers[i]);
				}
			}
		}
    //check containers in room
		for(unsigned int i = 0; i < currentRoom->containers.size(); i++){
			for(unsigned int j = 0; j < currentRoom->containers[i]->triggers.size(); j++){
				if(currentRoom->containers[i]->triggers[j].type != "used"){
					if(currentRoom->containers[i]->triggers[j].command == ""){
						nonCommandTriggers.push_back(&currentRoom->containers[i]->triggers[j]);
					}
					else{
						commandTriggers.push_back(&currentRoom->containers[i]->triggers[j]);
					}
				}
			}
		}
    //check items in room
		for(unsigned int i = 0; i < currentRoom->items.size(); i++){
			for(unsigned int j = 0; j < currentRoom->items[i]->triggers.size(); j++){
				if(currentRoom->items[i]->triggers[j].type != "used"){
					if(currentRoom->items[i]->triggers[j].command == ""){
						nonCommandTriggers.push_back(&currentRoom->items[i]->triggers[j]);
					}
					else{
						commandTriggers.push_back(&currentRoom->items[i]->triggers[j]);
					}
				}
			}
		}
    //check creatures in room
		for(unsigned int i = 0; i < currentRoom->creatures.size(); i++){
			for(unsigned int j = 0; j < currentRoom->creatures[i]->triggers.size(); j++){
				if(currentRoom->creatures[i]->triggers[j].type != "used"){
					if(currentRoom->creatures[i]->triggers[j].command == ""){
						nonCommandTriggers.push_back(&currentRoom->creatures[i]->triggers[j]);
					}
					else{
						commandTriggers.push_back(&currentRoom->creatures[i]->triggers[j]);
					}
				}
			}
		}

	}
  //check items in inventory
	for(unsigned int i = 0; i < inventory->items.size(); i++){
		for(unsigned int j = 0; j < inventory->items[i]->triggers.size(); j++){
			if(inventory->items[i]->triggers[j].type != "used"){
				if(inventory->items[i]->triggers[j].command == ""){
					nonCommandTriggers.push_back(&inventory->items[i]->triggers[j]);
				}
				else{
					commandTriggers.push_back(&inventory->items[i]->triggers[j]);
				}
			}
		}
	}

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

Container* Context::getContainer(string containerName){
	for(unsigned int i = 0; i < currentRoom->containers.size(); i++){
			if(currentRoom->containers[i]->name == containerName){
				return currentRoom->containers[i];
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
