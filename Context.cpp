#include "Context.hpp"
#include <iostream>
#include <string>

Context::Context(Room* startingRoom, Inventory* inventory){
  currentRoom = startingRoom;
  this->inventory = inventory;
}


void Context::parseContext(){
  /* Just commenting this out so it can compile
  if(currentRoom != NULL){
    for(unsigned int i = 0; i < currentRoom.triggers.size(); i++){
      if(currentRoom.triggers[i].command == NULL){

      }
      }
      }*/
}

Trigger& checkCommandTriggers(string input){

}

Trigger& checkNonCommandTriggers(){

}
