#include "Context.hpp"
#include <iostream>
#include <string>

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
			for(unsigned int j = 0; j < currentRoom->containers[i].triggers.size(); j++){

				if(currentRoom->containers[i].triggers[j].command == ""){
					nonCommandTriggers.push_back(&currentRoom->containers[i].triggers[j]);
				}
				else{
					commandTriggers.push_back(&currentRoom->containers[i].triggers[j]);
				}
			}
		}
    //check items in room
		for(unsigned int i = 0; i < currentRoom->containers.size(); i++){
			for(unsigned int j = 0; j < currentRoom->containers[i].triggers.size(); j++){

				if(currentRoom->items[i].triggers[j].command == ""){
					nonCommandTriggers.push_back(&currentRoom->items[i].triggers[j]);
				}
				else{
					commandTriggers.push_back(&currentRoom->items[i].triggers[j]);
				}
			}
		}
    //check creatures in room
		for(unsigned int i = 0; i < currentRoom->creatures.size(); i++){
			for(unsigned int j = 0; j < currentRoom->creatures[i].triggers.size(); j++){

				if(currentRoom->creatures[i].triggers[j].command == ""){
					nonCommandTriggers.push_back(&currentRoom->creatures[i].triggers[j]);
				}
				else{
					commandTriggers.push_back(&currentRoom->creatures[i].triggers[j]);
				}
			}
		}

	}
  //check items in inventory
	for(unsigned int i = 0; i < commandTriggers.size(); i++){
		cout << "commandTrigger command:" << commandTriggers[i]->command << std::endl;
	}

}

Trigger& checkCommandTriggers(string input){

}

Trigger& checkNonCommandTriggers(){

}
