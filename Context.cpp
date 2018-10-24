#include "Context.hpp"
#include <iostream>
#include <string>

Context::Context(Room& currentRoom, Inventory& currentInventory){
	this->currentRoom = currentRoom;
	this->currentInventory = currentInventory;
}


void Context::parseContext(){
	if(currentRoom != NULL){
		for(unsigned int i = 0; i < currentRoom.triggers.size(); i++){
			if(currentRoom.triggers[i].command == NULL){

			}
		}



	}


}
Trigger& checkCommandTriggers(string input){



}
Trigger& checkNonCommandTriggers(){

}
