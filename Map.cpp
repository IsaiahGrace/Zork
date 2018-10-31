#include "Map.hpp"
#include <iostream>
#include <string>

Map::Map(FILE *fptr) {
  //Determine the .xml file size
  fseek(fptr, 0, SEEK_END);
  long size = ftell(fptr);
  rewind(fptr);

  //Create a character array to hold the .xml file
  char *xml = (char *) malloc(size * sizeof(char));

  //read the contents of the xml file into the char array
  fread(xml, size, 1, fptr);

  //Parse the character array
  xml_document<> doc;
  doc.parse<0>(xml);

  //For each of the children of the Map node:
  xml_node<> *node = doc.first_node()->first_node();

  //THREE loops now. First loop initializes items, second initializes non room objects, third does rooms
  while(node) {
    string name = node->name();
    std::cout <<"Map: " << name << std::endl;

    //if(name == "room") rooms.push_back(Room(node));
    if(name == "item") items.push_back(Item(node));
    //else if(name == "container") containers.push_back(Container(node));
    //else if(name == "creature") creatures.push_back(Creature(node));

    node = node->next_sibling();
  }

  node = doc.first_node()->first_node();
  while(node) {
    string name = node->name();
    std::cout <<"Map: " << name << std::endl;

    if(name == "container") containers.push_back(Container(node,this));
    else if(name == "creature") creatures.push_back(Creature(node));

    node = node->next_sibling();
  }

  node = doc.first_node()->first_node();
  while(node) {
    string name = node->name();
    std::cout <<"Map: " << name << std::endl;


    if(name == "room") rooms.push_back(Room(node,this));
    node = node->next_sibling();
  }

  gameContext.inventory = &playerInventory;
  gameContext.currentRoom = this->getRoom("Entrance");

}

//returns the room that has same name as argument
Room* Map::getRoom(string roomname){
	for(unsigned int i = 0; i < rooms.size(); i++){
		if(rooms[i].name.compare(roomname) == 0){
			return &rooms[i];
		}
	}
	return NULL;
}

//searches rooms and containers to see if there is a name match, returns ptr if so. If no match, returns NULL
Owner* Map::getOwner(string ownerName){
	for(unsigned int i = 0; i < rooms.size(); i++){
			if(rooms[i].name.compare(ownerName) == 0){
				return &rooms[i];
			}
	}

	for(unsigned int i = 0; i < containers.size(); i++){
			if(containers[i].name.compare(ownerName) == 0){
				return &containers[i];
			}
	}

	return NULL;
}

Item* Map::getItem(string itemName){
	  for (unsigned int i = 0; i < items.size(); i++) {
		  if(items[i].name == itemName) return &items[i];
	  }
	  	  return NULL; // Item not parseAction
}


// parseAction command takes an input string and parses it to call other action funcitons.
// parseAction will print out an Error and not call any funcitons if the action string is not well formed.
// parseAction will not check to make sure that an action is valid in the current context.
void Map::parseAction(string input) {

  // Parse actions that have no operands
  if(input == "n") {
    this->move("n");
    return;
  } 
  if(input == "s") {
    this->move("s");
    return;
  } 
  if(input == "e") {
    this->move("e");
    return;
  } 
  if(input == "w") {
    this->move("w");
    return;
  } 
  if(input == "i") {
    this->playerInventory.printInventory();
    return;
  } 
  if(input == "open exit") {
    this->openExit();
    return;
  }
  
  // Parse action that have one opperand
  string action;
  string target;
  int breakPos;
  string container;
  string creature;
  string item;
  breakPos = input.find(" ", 0);
  action = input.substr(0,breakPos);
  target = input.substr(breakPos,breakPos);
  if(action == "" || target == "") {
    std::cout << "Error: Could not split action command into two words" << std::endl;
    return;
  }

  if(action == "take") {
    this->take(target);
    return;
  }
  if(action == "open") {
    this->open(target);
    return;
  }
  if(action == "read") {
    this->read(target);
    return;
  }
  if(action == "drop") {
    this->drop(target);
    return;
  }
  if(action == "put") {
    // parse target again and pass two strings to this->put()
    breakPos = target.find(" ",0);    
    item = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos + 1);
    container = target.substr(breakPos,breakPos);
    if(item == "" || container == "") {
      std::cout << "Error: could not parse the opperands of the put command" << std::endl;
    }
    this->put(item, container);
    return;
  }
  if(action == "trun") { // target will be "on item". this is the turn on command
    // parse target again and pass one item to this->turnOn()
    item = target.substr(3,3);
    if(item == "") {
      std::cout << "Error: could not parse the opperand of the turn on command" << std::endl;
    }
    this->turnOn(item);
    return;
  }
  if(action == "attack") {
    // parse target again and pass two strings to this->attack()
    breakPos = target.find(" ",0);    
    creature = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos + 1);
    item = target.substr(breakPos,breakPos);
    if(item == "" || creature == "") {
      std::cout << "Error: could not parse the opperands of the attack command" << std::endl;
    }
    this->put(item, container);
    return;
  }
  std::cout << "Error: could not match action string" << std::endl;
  return;
  
  // Mentioned in docs but we don't have to implement these
  // add
  // delete
  // update
  // Game Over
}
