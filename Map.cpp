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

Creature* Map::getCreature(string creatureName){
	  for (unsigned int i = 0; i < creatures.size(); i++) {
		  if(creatures[i].name == creatureName) return &creatures[i];
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
  if(input == "game over") {
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
    std::cout << "Error: Could not split action command into two words" << std::endl;
    return;
  }

  action = input.substr(0,breakPos);
  target = input.substr(breakPos+1);
  //std::cout << action << ":" << target << std::endl;

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
  if(action == "turn") { // target will be "on item". this is the turn on command
    // parse target again and pass one item to this->turnOn()
    if(target.length() < 3) {
      std::cout << "Error: could not parse the opperand of the turn on command" << std::endl;
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
      std::cout << "Error: Could not split the first half of put" << std::endl;
      return;
    }
    item = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos+1);
    if(breakPos == -1) {
      std::cout << "Error: Could not split the second half of put" << std::endl;
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
      std::cout << "Error: Could not split the first half of attack" << std::endl;
      return;
    }
    creature = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos + 1);
    if(breakPos == -1) {
      std::cout << "Error: Could not split the second half of attack" << std::endl;
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
      std::cout << "Error: Could not split the first half of add" << std::endl;
      return;
    }
    item = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos+1);
    if(breakPos == -1) {
      std::cout << "Error: Could not split the second half of add" << std::endl;
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
      std::cout << "Error: Could not split the first half of update" << std::endl;
      return;
    }
    item = target.substr(0,breakPos);
    breakPos = target.find(" ",breakPos+1);
    if(breakPos == -1) {
      std::cout << "Error: Could not split the second half of update" << std::endl;
      return;
    }
    status = target.substr(breakPos+1);
    this->update(item, status);
    return;
  }
  std::cout << "Error: could not match action string" << std::endl;
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
void Map::turnOn(string item){
	Item* itemobj = this->playerInventory.GetItem(item);
	if(itemobj == NULL){
		std::cout << "turnon Error: item does not exist in inventory" << std::endl;
		return;
	}
	if(itemobj->turnOn.size() == 0){
		std::cout << "turnon Error: item has no object" << std::endl;
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
		std::cout << "Attack Error: item does not exist in inventory" << std::endl;
		return;
	}

	Creature* creatureobj = this->gameContext.currentRoom->getCreature(creature);
	if(creatureobj == NULL){
		std::cout << "Attack Error: creature does not exist in room" << std::endl;
		return;
	}

	if(creatureobj->vulnerability != item){
		std::cout << "Attack Error: vulnerability does not match item" << std::endl;
	}


	for(unsigned int i = 0; i < creatureobj->attack.conditions.size();i++){
		if(creatureobj->attack.conditions[i].IsMet(this) == false){
			std::cout << "Attack Error: not all conditions met" << std::endl;
			return;
		}
	}
	std::cout << creatureobj->attack.print << std::endl;

	for(unsigned int i = 0; i < creatureobj->attack.actions.size(); i++){
		this->parseAction(creatureobj->attack.actions[i]);
	}
	return;
}
