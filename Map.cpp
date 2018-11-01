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
#ifndef RELEASE
    std::cout <<"Map: " << name << std::endl;
#endif
    if(name == "item") items.push_back(Item(node));
    
    node = node->next_sibling();
  }

  node = doc.first_node()->first_node();
  while(node) {
    string name = node->name();
#ifndef RELEASE
    std::cout <<"Map: " << name << std::endl;
#endif
    if(name == "container") containers.push_back(Container(node,this));
    else if(name == "creature") creatures.push_back(Creature(node));
    
    node = node->next_sibling();
  }

  node = doc.first_node()->first_node();
  while(node) {
    string name = node->name();
#ifndef RELEASE
    std::cout <<"Map: " << name << std::endl;
#endif

    if(name == "room") rooms.push_back(Room(node,this));
    node = node->next_sibling();
  }

  gameContext.inventory = &playerInventory;
  gameContext.currentRoom = this->getRoom("Entrance");
  std::cout << gameContext.currentRoom->description << std::endl;
  
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

	if(ownerName == "inventory"){
		return &playerInventory;
	}

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

Creature* Map::getCreature(string creatureName){
	  for (unsigned int i = 0; i < creatures.size(); i++) {
		  if(creatures[i].name == creatureName) return &creatures[i];
	  }
	  	  return NULL; // Item not parseAction
}

Container* Map::getContainer(string containerName){
	  for (unsigned int i = 0; i < containers.size(); i++) {
		  if(containers[i].name == containerName) return &containers[i];
	  }
	  	  return NULL; // Item not parseAction
}

// parseAction command takes an input string and parses it to call other action funcitons.
// parseAction will print out an Error and not call any funcitons if the action string is not well formed.
// parseAction will not check to make sure that an action is valid in the current context.
void Map::parseAction(string input) {

    if(input == "") {
#ifndef RELEASE
      std::cout << "parseAction Error: empty input string" << std::endl;
#endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif
      return;
    }
    input[0] = tolower(input[0]);
    //for(std::string::size_type i = 0; i < input.length(); i++) {
    //    input[i] = std::tolower(input[i]);
    //}
  // Parse actions that have no operands
  if(input == "n" || input == "s" || input == "e" || input == "w") {
    this->move(input);
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
  if(input == "game over" || input == "game Over") {
    throw 10;
    return;
  }

  // Parse action that have one opperand
  string action;
  string target;
  int breakPos;
  string container;
  string creature;
  string item;
  string owner;
  string status;
  breakPos = input.find(" ", 0);
  if(breakPos == -1) {
#ifndef RELEASE
    std::cout << "parseAction Error: Could not split action command into two words" << std::endl;
#endif
#ifdef RELEASE
    std::cout << "Error" << std::endl;
#endif
    return;
  }

  action = input.substr(0,breakPos);
  target = input.substr(breakPos+1);
#ifndef RELEASE
  std::cout << action << ":" << target << std::endl;
#endif
  
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
  if(action == "delete") {
    this->deleteItem(target);
    return;
  }
  if(action == "turn") { // target wil be "on item". this is the turn on command
    // parse target again and pass one item to this->turnOn()
    if(target.length() < 3) {
#ifndef RELEASE
      std::cout << "parseAction Error: could not parse the opperand of the turn on command" << std::endl;
#endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif
      return;
    }
    item = target.substr(3);
    this->turnOn(item);
    return;
  }
  if(action == "put") {
    // parse target again and pass two strings to this->put()
    breakPos = target.find(" ",0);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the first half of put" << std::endl;
#endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif
      
      return;
    }
    item = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos+1);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the second half of put" << std::endl;
#endif
#ifdef RELEASE
        std::cout << "Error" << std::endl;
#endif
        return;
    }
    container = target.substr(breakPos+1);
    this->put(item, container);
    return;
  }
  if(action == "attack") {
    // parse target again and pass two strings to this->attack()
    breakPos = target.find(" ",0);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the first half of attack" << std::endl;
#endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif
      return;
    }
    creature = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos + 1);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the second half of attack" << std::endl;
      #endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif
      return;
    }
    item = target.substr(breakPos+1);
    this->attack(creature, item);
    return;
  }
  if(action == "add") {
    // parse target again and pass two strings to this->put()
    breakPos = target.find(" ",0);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the first half of add" << std::endl;
#endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif
      
        return;
    }
    item = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos+1);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the second half of add" << std::endl;
#endif
#ifdef RELEASE
        std::cout << "Error" << std::endl;
#endif
        return;
    }
    owner = target.substr(breakPos+1);
    this->add(item, owner);
    return;
  }
    if(action == "update") {
    // parse target again and pass two strings to this->put()
    breakPos = target.find(" ",0);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the first half of update" << std::endl;
#endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif
      return;
    }
    item = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos+1);
    if(breakPos == -1) {
#ifndef RELEASE
      std::cout << "parseAction Error: Could not split the second half of update" << std::endl;
#endif
#ifdef RELEASE
      std::cout << "Error" << std::endl;
#endif 
      return;
    }
    status = target.substr(breakPos+1);
    this->update(item, status);
    return;
    }
#ifndef RELEASE
    std::cout << "parseAction Error: could not match action string: " << input << std::endl;
#endif
#ifdef RELEASE
    std::cout << "Error" << std::endl;
#endif
    return;
}

// For Debugging purposes
/*
void Map::move(string direction) {std::cout << "move:" << direction << std::endl;};
void Map::openExit() {std::cout << "open exit:" << std::endl;};
void Map::take(string item) {std::cout << "take:" << item  << std::endl;};
void Map::open(string container) {std::cout << "open:" << container << std::endl;};
void Map::read(string item) {std::cout << "read:" << item << std::endl;};
void Map::drop(string item) {std::cout << "drop:" << item << std::endl;};
void Map::put(string item, string container) {std::cout << "put:" << item << ":" << container << std::endl;};
void Map::turnOn(string item) {std::cout << "turnOn:" << item << std::endl;};
void Map::attack(string creature, string item) {std::cout << "attack:" << creature << ":" << item << std::endl;};
void Map::add(string item, string owner) {std::cout << "add:" << item << ":" << owner << std::endl;};
void Map::deleteItem(string item) {std::cout << "delete:" << item << std::endl;};
void Map::update(string item, string status) {std::cout << "update:" << item << ":" << status << std::endl;};
*/

void Map::move(string direction) {
  int numBorders = this->gameContext.currentRoom->borders.size();
  for(int i = 0; i < numBorders; i++) {
    if (direction[0] == this->gameContext.currentRoom->borders[i].direction[0]) {
      Room* potentialRoom = this->getRoom(this->gameContext.currentRoom->borders[i].name);
      if(potentialRoom == NULL){
#ifndef RELEASE
	std::cout << "move error: room referenced by border does not exist." << std::endl;
#endif
      }
      else {
	this->gameContext.currentRoom = potentialRoom;
#ifndef RELEASE
	std::cout << "moved " << direction << " to :" << this->gameContext.currentRoom->name << std::endl;
#endif
	std::cout << this->gameContext.currentRoom->description << std::endl;
	return;
      }
    }
  }
#ifndef RELEASE
  std::cout << "move Error: unable to find room from direction: " << direction << std::endl;
#endif
#ifdef RELEASE
  std::cout << "Error" << std::endl;
#endif
  return;
}

void Map::openExit() {
  if (this->gameContext.currentRoom->isExit) {
    throw 10;
  }
#ifndef RELEASE
  std::cout << "openExit Error: currentRoom is not an exit room" << std::endl;
#endif
}

void Map::turnOn(string item){
  Item* itemobj = this->playerInventory.GetItem(item);
  if(itemobj == NULL){
#ifndef RELEASE
    std::cout << "turnon Error: item does not exist in inventory" << std::endl;
#endif
    return;
  }
  if(itemobj->turnOn.size() == 0){
#ifndef RELEASE
    std::cout << "turnon Error: item has no object" << std::endl;
#endif
    return;
  }
  std::cout << itemobj->turnOn[0].printText << std::endl;

  for(unsigned int i = 0; i < itemobj->turnOn[0].action.size(); i++){
    this->parseAction(itemobj->turnOn[0].action[i]);
  }
  return;
}

void Map::attack(string creature, string item){
	Item* itemobj = this->playerInventory.GetItem(item);
	if(itemobj == NULL){
#ifndef RELEASE
		std::cout << "Attack Error: item does not exist in inventory" << std::endl;
#endif
#ifdef RELEASE
		std::cout << "You don't have that item in your inventory" << std::endl;
#endif
		return;
	}

	Creature* creatureobj = this->gameContext.currentRoom->getCreature(creature);
	if(creatureobj == NULL){
#ifndef RELEASE
		std::cout << "Attack Error: creature does not exist in room" << std::endl;
#endif
		return;
	}

	if(creatureobj->vulnerability != item){
#ifndef RELEASE
		std::cout << "Attack Error: vulnerability does not match item" << std::endl;
#endif
#ifdef RELEASE
		std::cout << "The attack was not very successful" << std::endl;
#endif
	}


	for(unsigned int i = 0; i < creatureobj->attack.conditions.size();i++){
		if(creatureobj->attack.conditions[i].IsMet(this) == false){
#ifndef RELEASE
			std::cout << "Attack Error: not all conditions met" << std::endl;
#endif
			return;
		}
	}

	std::cout << creatureobj->attack.print << std::endl;
#ifndef RELEASE
	std::cout << "Attack action size: " << creatureobj->attack.actions.size() << std::endl;
#endif
	for(unsigned int i = 0; i < creatureobj->attack.actions.size(); i++){
		this->parseAction(creatureobj->attack.actions[i]);
	}
	return;
}

void Map::put(string item, string owner){
	//std::cout <<"puttingitem" <<std::endl;
	Item* itemobj = this->gameContext.getItem(item);
	if(itemobj == NULL){
#ifndef RELEASE
		std::cout << "put Error: item does not exist in context" << std::endl;
#endif
		return;
	}
	Owner* ownerobj = this->gameContext.getOwner(owner);
	if(ownerobj == NULL){
#ifndef RELEASE
		std::cout << "put Error: owner does not exist in context" << std::endl;
#endif
	}
	this->deleteItem(item);

	ownerobj->items.push_back(itemobj);
}

void Map::drop(string item){
	this->put(item,"room");
}

void Map::take(string item){
	this->put(item,"inventory");
}

void Map::deleteItem(string itemname){
	for(unsigned int i = 0; i < rooms.size(); i++){

		//checks all items in all containers in each room
		for(unsigned int j = 0; j < rooms[i].containers.size(); j++){
			for(unsigned int k = 0; k < rooms[i].containers[j]->items.size(); k++){
				if(rooms[i].containers[j]->items[k]->name == itemname){
					rooms[i].containers[j]->items.erase(rooms[i].containers[j]->items.begin()+k);
				}
			}
		}
		//checks items in each room
		for(unsigned int q = 0; q < rooms[i].items.size(); q++){
			if(rooms[i].items[q]->name == itemname){
				rooms[i].items.erase(rooms[i].items.begin()+q);
			}
		}
	}

	//checks all items in inventory
	for(unsigned int i = 0; i < playerInventory.items.size(); i++){
		if(playerInventory.items[i]->name == itemname){
			playerInventory.items.erase(playerInventory.items.begin() + i);
		}
	}
	// Search room names
	if (this->gameContext.currentRoom->name != itemname) {
        for (unsigned int i = 0; i < this->rooms.size(); i++) {
            if (itemname == this->rooms[i].name) {
                this->rooms.erase(this->rooms.begin() + i);
            }
        }
    }
	//std::cout << "items deleted successfully?" << std::endl;
}

void Map::update(string item, string status){
	Base* baseobj = this->getBase(item);
	if(baseobj == NULL){
#ifndef RELEASE
		std::cout << "update error: no item to update" << std::endl;
#endif
		return;
	}

	baseobj->status = status;

}

Base* Map::getBase(string basename){
	Base* potentialBase = this->getContainer(basename);
	if(potentialBase != NULL){
		return potentialBase;
	}

	potentialBase = this->getCreature(basename);
	if(potentialBase != NULL){
		return potentialBase;
	}

	potentialBase = this->getItem(basename);
	if(potentialBase != NULL){
		return potentialBase;
	}

	potentialBase = this->getRoom(basename);
	if(potentialBase != NULL){
		return potentialBase;
	}
	return NULL;
}

void Map::add(string itemname,string ownername){

	//TODO: define this. Can it add creatures/containers to rooms? or does it just add items
	if(ownername == "inventory"){
#ifndef RELEASE
		std::cout << "add Error: cannot add objects to inventory" << std::endl;
#endif
		return;
	}

	Item* baseobj = this->getItem(itemname);
	if(baseobj == NULL){
#ifndef RELEASE
		std::cout << "add Error: object to be added does not exist" << std::endl;
#endif
		return;
	}

	Owner* ownerobj = this->getOwner(ownername);
	if(ownerobj == NULL){
#ifndef RELEASE
		std::cout << "add Error: owner does not exist in context" << std::endl;
#endif
		return;
	}

	ownerobj->items.push_back(baseobj);
#ifndef RELEASE
	std::cout << "item successfully added" << std::endl;
#endif
}

void Map::read(string itemname){
	Item* itemobj = this->playerInventory.getItem(itemname);
	if(itemobj == NULL){
#ifndef RELEASE
		std::cout << "Read Error: item does not exist in inventory" << std::endl;
#endif
		return;
	}

	if(itemobj->writing == ""){
		std:: cout << "Nothing written" << std::endl;
		return;
	}

	std::cout << itemobj->writing << std::endl;
}

void Map::open(string containername){
	Container* containerobj = this->gameContext.getContainer(containername);
	if(containerobj == NULL){
#ifndef RELEASE
		std::cout << "open error: container does not exist in context";
#endif
	}

	std::cout << containerobj->name;
	unsigned int numitems = containerobj->items.size();
	if(numitems == 0){
		std::cout << " is empty." << std::endl;
		return;
	}
	std::cout << " contains:";
	for(unsigned int i = 0; i < numitems; i++){
	  std::cout << " " << containerobj->items[i]->name;
	  if(i != numitems - 1) {
	    std::cout << ", ";
	  }
	}
	std::cout << std::endl;
	containerobj->status = "unlocked";
}
