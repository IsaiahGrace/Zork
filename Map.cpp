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

    if(name == "container") containers.push_back(Container(node));
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


